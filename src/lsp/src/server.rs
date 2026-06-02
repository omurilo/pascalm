use crop::Rope;
use dashmap::DashMap;
use pascalm::{}
use log::debug;
use serde_json::Value;
use tower_lsp::lsp_types::*;
use tower_lsp::jsonrpc::Result;
use tower_lsp::{
    Client, LanguageServer, LspService, Server
};

struct TextDocumentChange<'a> {
    uri: String,
    text: &'a str,
}

#[derive(Debug)]
struct Backend {
    client: Client,
    document_map: DashMap<String, Rope>,
    semanticast_map: DashMap<String, Rope>,
}

impl Backend {
    fn new(client: tower_lsp::Client) -> Self {
        Self {
            client,
            documents: DashMap::new(),
        }
    }

    async fn on_change(&self, item: TextDocumentChange<'_>) {
        let rope = Rope::from(item.text);
        let compile_result = compile(item.text);
        let mut diagnostics = compile_result
            .diagnostics
            .iter()
            .flat_map(|d| {
                d.labels.iter().filter_map(|label| {
                    let start = offset_to_position(label.range.start, &rope)?;
                    let end = offset_to_position(label.range.end, &rope)?;
                    let diag = Diagnostic {
                        range: Range::new(start, end),
                        severity: None,
                        code: None,
                        code_description: None,
                        source: None,
                        message: format!("{:?}", d.message),
                        related_information: None,
                        tags: None,
                        data: None,
                    };
                    Some(diag)
                })
            })
            .collect::<Vec<_>>();
        compile_result.semantic.errors.iter().for_each(|sem_err| {
            let span = sem_err.span;
            let start = offset_to_position(span.start as usize, &rope);
            let end = offset_to_position(span.end as usize, &rope);
            if let (Some(start), Some(end)) = (start, end) {
                let diag = Diagnostic {
                    range: Range::new(start, end),
                    severity: None,
                    code: None,
                    code_description: None,
                    source: None,
                    message: sem_err.message.to_string(),
                    related_information: None,
                    tags: None,
                    data: None,
                };
                diagnostics.push(diag);
            }
        });

        let uri =
            Url::parse(&item.uri).unwrap_or_else(|_| Url::from_directory_path(&item.uri).unwrap());
        self.client
            .publish_diagnostics(uri, diagnostics, None)
            .await;
        self.semanticast_map
            .insert(item.uri.clone(), compile_result);
        self.document_map.insert(item.uri.clone(), rope);
    }

    fn get_definition(&self, params: GotoDefinitionParams) -> Option<GotoDefinitionResponse> {
        let uri = params
            .text_document_position_params
            .text_document
            .uri
            .to_string();
        let position = params.text_document_position_params.position;

        let rope = self.document_map.get(&uri)?;

        let compilation_result = self.semanticast_map.get(&uri)?;
        let offset = position_to_offset(position, &rope)?;
        if let Some(interval) = compilation_result
            .semantic
            .span_to_symbol
            .find(offset, offset + 1)
            .next()
        {
            let start = offset_to_position(interval.start, &rope)?;
            let end = offset_to_position(interval.stop, &rope)?;
            let location = Location::new(
                params.text_document_position_params.text_document.uri,
                Range::new(start, end),
            );
            return Some(GotoDefinitionResponse::Scalar(location));
        };
        let ref_id = compilation_result
            .semantic
            .span_to_reference
            .find(offset, offset + 1)
            .next()?
            .val;
        let symbol_id = compilation_result.semantic.references[ref_id]?;
        let symbol_span = compilation_result.semantic.get_symbol_span(symbol_id);
        let start = offset_to_position(symbol_span.start as usize, &rope)?;
        let end = offset_to_position(symbol_span.end as usize, &rope)?;
        let location = Location::new(
            params.text_document_position_params.text_document.uri,
            Range::new(start, end),
        );

        Some(GotoDefinitionResponse::Scalar(location))
    }

    fn offset_to_position(offset: usize, rope: &Rope) -> Option<Position> {
    if offset > rope.byte_len() {
        return None;
    }
    let line = rope.line_of_byte(offset);
    let line_start_byte = rope.byte_of_line(line);
    let column = offset - line_start_byte;
    Some(Position::new(line as u32, column as u32))
}

fn position_to_offset(position: Position, rope: &Rope) -> Option<usize> {
    if position.line as usize >= rope.line_len() {
        return None;
    }
    let line_byte_offset = rope.byte_of_line(position.line as usize);
    Some(line_byte_offset + position.character as usize)
}
}

#[tower_lsp::async_trait]
impl LanguageServer for Backend {
    async fn initialize(&self, _: InitializeParams) -> Result<InitializeResult> {
        Ok(InitializeResult {
            capabilities: ServerCapabilities {
                document_formatting_provider: Some(OneOf::Left(true)),
                inlay_hint_provider: Some(OneOf::Left(true)),
                text_document_sync: Some(TextDocumentSyncCapability::Options(
                    TextDocumentSyncOptions {
                        open_close: Some(true),
                        change: Some(TextDocumentSyncKind::FULL),
                        save: Some(TextDocumentSyncSaveOptions::SaveOptions(SaveOptions {
                            include_text: Some(true),
                        })),
                        ..Default::default()
                    },
                )),
                hover_provider: Some(HoverProviderCapability::Simple(true)),
                completion_provider: Some(CompletionOptions {
                    resolve_provider: Some(false),
                    trigger_characters: Some(vec![".".to_string()]),
                    work_done_progress_options: Default::default(),
                    all_commit_characters: None,
                    completion_item: None,
                }),
                workspace: Some(WorkspaceServerCapabilities {
                    workspace_folders: Some(WorkspaceFoldersServerCapabilities {
                        supported: Some(true),
                        change_notifications: Some(OneOf::Left(true)),
                    }),
                    file_operations: None,
                }),
                semantic_tokens_provider: Some(
                    SemanticTokensServerCapabilities::SemanticTokensRegistrationOptions(
                        SemanticTokensRegistrationOptions {
                            text_document_registration_options: {
                                TextDocumentRegistrationOptions {
                                    document_selector: Some(vec![DocumentFilter {
                                        language: Some("l".to_string()),
                                        scheme: Some("file".to_string()),
                                        pattern: None,
                                    }]),
                                }
                            },
                            semantic_tokens_options: SemanticTokensOptions {
                                work_done_progress_options: WorkDoneProgressOptions::default(),
                                legend: SemanticTokensLegend {
                                    token_types: vec![
                                        SemanticTokenType::FUNCTION,
                                        SemanticTokenType::VARIABLE,
                                        SemanticTokenType::PARAMETER,
                                        SemanticTokenType::STRUCT,
                                        SemanticTokenType::PROPERTY,
                                    ],
                                    token_modifiers: vec![],
                                },
                                range: Some(true),
                                full: Some(SemanticTokensFullOptions::Bool(true)),
                            },
                            static_registration_options: StaticRegistrationOptions::default(),
                        },
                    ),
                ),
                definition_provider: Some(OneOf::Left(true)),
                references_provider: Some(OneOf::Left(true)),
                rename_provider: Some(OneOf::Left(true)),
                ..Default::default()
            },
            server_info: Some(ServerInfo {
                name: "pascalmls".to_string(),
                version: Some("0.0.1".to_string()),
            }),
        })
    }

    async fn initialized(&self, _: InitializedParams) {
        self.client
            .log_message(MessageType::INFO, "Pascalm LSP Initialized")
            .await;
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        self.on_change(TextDocumentChange {
            uri: params.text_document.uri.to_string(),
            text: &params.text_document.text,
        })
        .await;
        debug!("file opened!");
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        self.on_change(TextDocumentChange {
            text: &params.content_changes[0].text,
            uri: params.text_document.uri.to_string(),
        })
        .await;
    }

    async fn did_close(&self, params: DidCloseTextDocumentParams) {
        let uri = params.text_document.uri.to_string();
        self.document_map.remove(&uri);

        self.client
            .publish_diagnostics(params.text_document.uri, vec![], None)
            .await;
    }

    async fn did_save(&self, params: DidSaveTextDocumentParams) {
        let uri = params.text_document.uri.to_string();

        debug!("file saved");

        if let Some(text) = self.document_map.get(&uri) {
            // Check grammar and get diagnostics
            // let diagnostics = self.check_grammar(&params.text_document.uri, &text).await;

            // Publish diagnostics back to the client
            // self.client
            //     .publish_diagnostics(params.text_document.uri, diagnostics, None)
            //     .await;
        }
    }

    async fn goto_definition(
        &self,
        params: GotoDefinitionParams,
    ) -> Result<Option<GotoDefinitionResponse>> {
        let definition = self.get_definition(params);
        Ok(definition)
    }

    async fn references(&self, params: ReferenceParams) -> Result<Option<Vec<Location>>> {
        let uri = params.text_document_position.text_document.uri.to_string();
        let position = params.text_document_position.position;
        let references = self.get_references(uri, position, params.context.include_declaration);
        Ok(references)
    }

    async fn semantic_tokens_full(
        &self,
        params: SemanticTokensParams,
    ) -> Result<Option<SemanticTokensResult>> {
        let uri = params.text_document.uri.to_string();
        let semantic_tokens = self.build_semantic_tokens(&uri);
        if let Some(tokens) = semantic_tokens {
            return Ok(Some(SemanticTokensResult::Tokens(SemanticTokens {
                result_id: None,
                data: tokens,
            })));
        }
        Ok(None)
    }

    async fn semantic_tokens_range(
        &self,
        params: SemanticTokensRangeParams,
    ) -> Result<Option<SemanticTokensRangeResult>> {
        let uri = params.text_document.uri.to_string();
        let range = params.range;
        let semantic_tokens = self.build_semantic_tokens_range(&uri, range);
        Ok(semantic_tokens.map(|data| {
            SemanticTokensRangeResult::Tokens(SemanticTokens {
                result_id: None,
                data,
            })
        }))
    }

    async fn hover(&self, params: HoverParams) -> Result<Option<Hover>> {
        let uri = params
            .text_document_position_params
            .text_document
            .uri
            .to_string();
        let position = params.text_document_position_params.position;

        let rope = self.document_map.get(&uri);
        let compilation_result = self.semanticast_map.get(&uri);

        let hover = (|| -> Option<Hover> {
            let rope = rope.as_deref()?;
            let compilation_result = compilation_result.as_deref()?;
            let offset = position_to_offset(position, rope)?;
            let symbol_id = compilation_result.semantic.get_symbol_at(offset)?;

            let symbol_kind = compilation_result.semantic.get_symbol_kind(symbol_id);
            let type_info = &compilation_result.semantic.bindings[symbol_id];
            let span = compilation_result.semantic.get_symbol_span(symbol_id);
            let name = rope
                .byte_slice(span.start as usize..span.end as usize)
                .to_string();

            let content = match symbol_kind {
                SymbolKind::Function => format!("```l\nfn {name}\n```"),
                SymbolKind::Struct => format!("```l\nstruct {name}\n```"),
                _ => {
                    let type_str = type_info
                        .ty
                        .format_literal_type(&compilation_result.semantic);
                    match symbol_kind {
                        SymbolKind::Variable => format!("```l\nlet {name}: {type_str}\n```"),
                        SymbolKind::Parameter => format!("```l\n{name}: {type_str}\n```"),
                        SymbolKind::Field => format!("```l\n{name}: {type_str}\n```"),
                        _ => return None,
                    }
                }
            };

            Some(Hover {
                contents: HoverContents::Markup(MarkupContent {
                    kind: MarkupKind::Markdown,
                    value: content,
                }),
                range: None,
            })
        })();

        Ok(hover)
    }

    async fn inlay_hint(
        &self,
        params: tower_lsp::lsp_types::InlayHintParams,
    ) -> Result<Option<Vec<InlayHint>>> {
        Ok(self.build_inlay_hints(params.text_document.uri.as_ref()))
    }

    async fn completion(&self, params: CompletionParams) -> Result<Option<CompletionResponse>> {
        let completions = self.get_completion(params);
        Ok(completions.map(CompletionResponse::Array))
    }

    async fn rename(&self, params: RenameParams) -> Result<Option<WorkspaceEdit>> {
        let uri = params.text_document_position.text_document.uri.to_string();
        let position = params.text_document_position.position;
        let new_name = params.new_name;
        let workspace_edit = self.get_rename_edit(uri, position, new_name);
        Ok(workspace_edit)
    }

    async fn formatting(&self, params: DocumentFormattingParams) -> Result<Option<Vec<TextEdit>>> {
        Ok(self.format_text(params))
    }

    async fn did_change_configuration(&self, _: DidChangeConfigurationParams) {
        debug!("configuration changed!");
    }

    async fn did_change_workspace_folders(&self, _: DidChangeWorkspaceFoldersParams) {
        debug!("workspace folders changed!");
    }

    async fn did_change_watched_files(&self, _: DidChangeWatchedFilesParams) {
        debug!("watched files have changed!");
    }
}

#[tokio::main]
async fn main() {
    env_logger::init();

    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::build(|client| Backend {
        client,
        semanticast_map: DashMap::new(),
        document_map: DashMap::new(),
    })
    .finish();

    Server::new(stdin, stdout, socket).serve(service).await;
}

