//! End-to-end tests for the `pascalmls` language server.
//!
//! Each test spawns the built binary and drives it over stdio with real
//! JSON-RPC (LSP) messages, then asserts on the responses — the same checks one
//! would do by hand in an editor, but automated. Run with `cargo test`.

use serde_json::{json, Value};
use std::io::{BufReader, Read, Write};
use std::process::{Child, ChildStdin, Command, Stdio};
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

/// A spawned language server with a tiny JSON-RPC client over its stdio.
struct Server {
    child: Child,
    stdin: ChildStdin,
    /// Every message the server has sent so far (responses + notifications),
    /// filled by a background reader thread. Matched messages are removed.
    msgs: Arc<Mutex<Vec<Value>>>,
    next_id: i64,
}

impl Server {
    fn start() -> Self {
        let mut child = Command::new(env!("CARGO_BIN_EXE_pascalmls"))
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .stderr(Stdio::null())
            .spawn()
            .expect("failed to spawn pascalmls");

        let stdin = child.stdin.take().unwrap();
        let stdout = child.stdout.take().unwrap();
        let msgs = Arc::new(Mutex::new(Vec::new()));
        let msgs_reader = Arc::clone(&msgs);

        std::thread::spawn(move || {
            let mut reader = BufReader::new(stdout);
            while let Some(value) = read_message(&mut reader) {
                msgs_reader.lock().unwrap().push(value);
            }
        });

        Server {
            child,
            stdin,
            msgs,
            next_id: 0,
        }
    }

    fn send(&mut self, msg: Value) {
        let body = serde_json::to_vec(&msg).unwrap();
        write!(self.stdin, "Content-Length: {}\r\n\r\n", body.len()).unwrap();
        self.stdin.write_all(&body).unwrap();
        self.stdin.flush().unwrap();
    }

    fn notify(&mut self, method: &str, params: Value) {
        self.send(json!({ "jsonrpc": "2.0", "method": method, "params": params }));
    }

    /// Retry a request until its `result` satisfies `ready` (covers the async
    /// `did_open`: the document may not be analyzed yet when we first ask).
    fn request_until(
        &mut self,
        method: &str,
        params: Value,
        ready: impl Fn(&Value) -> bool,
    ) -> Value {
        for _ in 0..50 {
            let resp = self.request(method, params.clone());
            if ready(&resp["result"]) {
                return resp;
            }
            std::thread::sleep(Duration::from_millis(100));
        }
        panic!("{method} never became ready");
    }

    /// Send a request and block until its response arrives (or panic on timeout).
    fn request(&mut self, method: &str, params: Value) -> Value {
        self.next_id += 1;
        let id = self.next_id;
        self.send(json!({ "jsonrpc": "2.0", "id": id, "method": method, "params": params }));
        self.recv(Duration::from_secs(15), |m| m.get("id").and_then(Value::as_i64) == Some(id))
            .unwrap_or_else(|| panic!("timed out waiting for response to {method}"))
    }

    /// Poll received messages for the first one matching `pred`, removing it.
    fn recv(&self, timeout: Duration, pred: impl Fn(&Value) -> bool) -> Option<Value> {
        let deadline = Instant::now() + timeout;
        loop {
            {
                let mut msgs = self.msgs.lock().unwrap();
                if let Some(pos) = msgs.iter().position(&pred) {
                    return Some(msgs.remove(pos));
                }
            }
            if Instant::now() >= deadline {
                return None;
            }
            std::thread::sleep(Duration::from_millis(10));
        }
    }

    fn initialize(&mut self, root_uri: Option<&str>) {
        let params = json!({
            "capabilities": {},
            "rootUri": root_uri,
        });
        self.request("initialize", params);
        self.notify("initialized", json!({}));
    }

    fn did_open(&mut self, uri: &str, text: &str) {
        self.notify(
            "textDocument/didOpen",
            json!({
                "textDocument": { "uri": uri, "languageId": "pascalm", "version": 1, "text": text }
            }),
        );
    }

    /// Wait for a `window/logMessage` whose text contains `needle`.
    fn wait_log_containing(&self, needle: &str) -> String {
        self.recv(Duration::from_secs(15), |m| {
            m.get("method").and_then(Value::as_str) == Some("window/logMessage")
                && m["params"]["message"]
                    .as_str()
                    .map(|s| s.contains(needle))
                    .unwrap_or(false)
        })
        .map(|m| m["params"]["message"].as_str().unwrap().to_string())
        .unwrap_or_else(|| panic!("no logMessage containing {needle:?}"))
    }
}

impl Drop for Server {
    fn drop(&mut self) {
        let _ = self.child.kill();
        let _ = self.child.wait();
    }
}

/// Read one Content-Length-framed JSON-RPC message. Returns None on EOF.
fn read_message(reader: &mut BufReader<impl Read>) -> Option<Value> {
    use std::io::BufRead;
    let mut content_length = 0usize;
    loop {
        let mut line = String::new();
        if reader.read_line(&mut line).ok()? == 0 {
            return None; // EOF
        }
        let trimmed = line.trim_end();
        if trimmed.is_empty() {
            break; // end of headers
        }
        if let Some(rest) = trimmed.strip_prefix("Content-Length:") {
            content_length = rest.trim().parse().ok()?;
        }
    }
    let mut body = vec![0u8; content_length];
    reader.read_exact(&mut body).ok()?;
    serde_json::from_slice(&body).ok()
}

const SAMPLE: &str = "\
program Sample;
var
  x: integer;
  y: integer;
procedure Inc(val: integer);
begin
  val := val + 1; { only local }
end;
begin
  x := 1;
  y := 2;
  writeln(x); { print x }
end.
";

fn edits_of(workspace_edit: &Value) -> Vec<Value> {
    workspace_edit["changes"]
        .as_object()
        .and_then(|m| m.values().next())
        .and_then(Value::as_array)
        .cloned()
        .unwrap_or_default()
}

#[test]
fn formatting_keeps_trailing_comment_on_its_statement() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    let resp = s.request_until(
        "textDocument/formatting",
        json!({
            "textDocument": { "uri": uri },
            "options": { "tabSize": 2, "insertSpaces": true }
        }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let edits = resp["result"].as_array().expect("formatting returned edits");
    let text = edits[0]["newText"].as_str().unwrap();

    assert!(
        text.contains("val := val + 1;  { only local }"),
        "trailing comment not kept on its statement:\n{text}"
    );
    assert!(
        !text.contains("end;  { only local }"),
        "trailing comment drifted onto `end`:\n{text}"
    );
    assert!(
        text.contains("writeln(x);  { print x }"),
        "trailing comment on writeln misplaced:\n{text}"
    );
}

#[test]
fn rename_only_touches_the_target_symbol() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    // Rename `x` from its use on the `x := 1;` line (line 9, char 2).
    let resp = s.request(
        "textDocument/rename",
        json!({
            "textDocument": { "uri": uri },
            "position": { "line": 9, "character": 2 },
            "newName": "counter"
        }),
    );
    let edits = edits_of(&resp["result"]);
    assert_eq!(
        edits.len(),
        3,
        "expected 3 edits (decl + 2 uses of x), got {}: {resp}",
        edits.len()
    );
    for e in &edits {
        assert_eq!(e["newText"], "counter");
    }
}

#[test]
fn rename_refuses_builtin() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    // `writeln` is on line 11; renaming a builtin must be refused (null result).
    let resp = s.request(
        "textDocument/rename",
        json!({
            "textDocument": { "uri": uri },
            "position": { "line": 11, "character": 2 },
            "newName": "nope"
        }),
    );
    assert!(
        resp["result"].is_null(),
        "renaming a builtin should be refused, got {resp}"
    );
}

#[test]
fn references_include_declaration_and_uses() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    // Cursor on the `x` in `x := 1;` (line 9). With includeDeclaration, the
    // result is the declaration (line 2) + both uses (lines 9 and 11).
    let resp = s.request_until(
        "textDocument/references",
        json!({
            "textDocument": { "uri": uri },
            "position": { "line": 9, "character": 2 },
            "context": { "includeDeclaration": true }
        }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let locs = resp["result"].as_array().unwrap();
    assert_eq!(
        locs.len(),
        3,
        "expected decl + 2 uses of x, got {}: {resp}",
        locs.len()
    );
    for l in locs {
        assert_eq!(l["uri"], uri, "references should be in the same file");
    }
}

#[test]
fn references_exclude_declaration_when_not_requested() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    let resp = s.request_until(
        "textDocument/references",
        json!({
            "textDocument": { "uri": uri },
            "position": { "line": 9, "character": 2 },
            "context": { "includeDeclaration": false }
        }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let locs = resp["result"].as_array().unwrap();
    assert_eq!(
        locs.len(),
        2,
        "expected only the 2 uses of x (no declaration), got {}: {resp}",
        locs.len()
    );
}

#[test]
fn semantic_tokens_are_produced() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    let resp = s.request_until(
        "textDocument/semanticTokens/full",
        json!({ "textDocument": { "uri": uri } }),
        |r| r["data"].as_array().map_or(false, |a| !a.is_empty()),
    );
    let data = resp["result"]["data"].as_array().expect("tokens data array");
    assert!(!data.is_empty(), "expected some semantic tokens");
    assert_eq!(data.len() % 5, 0, "token data must come in groups of 5");
}

#[test]
fn goto_definition_jumps_into_a_used_unit() {
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/xfile");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed"); // workspace indexed/analyzed
    s.did_open(&prog_uri, &text);

    // `writeln(triple(3))` is on line 4; `triple` comes from `uses mylib`.
    let resp = s.request_until(
        "textDocument/definition",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 4, "character": 10 }
        }),
        |r| !r.is_null(),
    );
    let result = resp["result"].clone();
    let uri = result["uri"].as_str().unwrap_or("");
    assert!(
        uri.ends_with("mylib.pas"),
        "definition should land in mylib.pas, got: {result}"
    );
    let start = &result["range"]["start"];
    assert!(
        !(start["line"] == 0 && start["character"] == 0),
        "definition range looks empty: {result}"
    );
}

#[test]
fn hover_resolves_symbol_from_a_used_unit() {
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/xfile");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed");
    s.did_open(&prog_uri, &text);

    // Hover over `triple` (from `uses mylib`) should show its imported signature.
    let resp = s.request_until(
        "textDocument/hover",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 4, "character": 10 }
        }),
        |r| !r.is_null(),
    );
    let value = resp["result"]["contents"]["value"]
        .as_str()
        .unwrap_or("");
    assert!(
        value.contains("triple"),
        "hover should describe the imported symbol, got: {}",
        resp["result"]
    );
}

#[test]
fn goto_definition_resolves_path_style_uses() {
    // `uses sub/mylib` (a path spec) must resolve to the unit's file too — the
    // index is keyed by bare stem, so the lookup matches the last path segment.
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/xfile_path");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed");
    s.did_open(&prog_uri, &text);

    let resp = s.request_until(
        "textDocument/definition",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 4, "character": 10 }
        }),
        |r| !r.is_null(),
    );
    let uri = resp["result"]["uri"].as_str().unwrap_or("");
    assert!(
        uri.ends_with("mylib.pas"),
        "path-style `uses` should resolve into mylib.pas, got: {}",
        resp["result"]
    );
}

#[test]
fn goto_and_hover_resolve_stdlib_symbols() {
    // `Sqrt` comes from the implicit `system` stdlib unit, which is embedded
    // (no file on disk). The server materializes it to a cache file so both
    // hover and go-to-definition work.
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/stdlib");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed");
    s.did_open(&prog_uri, &text);

    // `Sqrt` is on line 3, char 10.
    let hover = s.request_until(
        "textDocument/hover",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 3, "character": 10 }
        }),
        |r| !r.is_null(),
    );
    let value = hover["result"]["contents"]["value"].as_str().unwrap_or("");
    assert!(
        value.contains("Sqrt"),
        "hover should describe the stdlib symbol, got: {}",
        hover["result"]
    );

    let goto = s.request_until(
        "textDocument/definition",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 3, "character": 10 }
        }),
        |r| !r.is_null(),
    );
    let uri = goto["result"]["uri"].as_str().unwrap_or("");
    assert!(
        uri.ends_with("system.pas"),
        "go-to-definition should land in the materialized system.pas, got: {}",
        goto["result"]
    );
}

#[test]
fn workspace_units_are_analyzed_on_init() {
    // Point the server at the repo's multi-unit fixture and confirm it indexes
    // and analyzes the units (the foundation for cross-file features).
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/../tests/success/18-units");
    let uri = format!("file://{dir}");

    let mut s = Server::start();
    s.initialize(Some(&uri));

    let log = s.wait_log_containing("analyzed");
    // e.g. "Pascalm LSP initialized — indexed 5, analyzed 4 unit(s) under …"
    let analyzed: i64 = log
        .split("analyzed")
        .nth(1)
        .and_then(|s| s.trim().split_whitespace().next())
        .and_then(|n| n.parse().ok())
        .unwrap_or(0);
    assert!(analyzed > 0, "expected some analyzed units, log was: {log}");
}

#[test]
fn completion_offers_symbols_and_keywords() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    let resp = s.request_until(
        "textDocument/completion",
        json!({
            "textDocument": { "uri": uri },
            "position": { "line": 10, "character": 0 }
        }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let labels: Vec<&str> = resp["result"]
        .as_array()
        .unwrap()
        .iter()
        .filter_map(|i| i["label"].as_str())
        .collect();

    // Local declarations from the file.
    assert!(labels.contains(&"x"), "completion missing local `x`: {labels:?}");
    assert!(labels.contains(&"Inc"), "completion missing proc `Inc`: {labels:?}");
    // Language keywords are always offered.
    assert!(
        labels.contains(&"begin"),
        "completion missing keyword `begin`: {labels:?}"
    );
}

#[test]
fn document_symbols_outline_the_file() {
    let mut s = Server::start();
    s.initialize(None);
    let uri = "file:///sample.pascalm";
    s.did_open(uri, SAMPLE);

    let resp = s.request_until(
        "textDocument/documentSymbol",
        json!({ "textDocument": { "uri": uri } }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let syms = resp["result"].as_array().unwrap();
    let names: Vec<&str> = syms.iter().filter_map(|s| s["name"].as_str()).collect();

    // Top-level vars and the procedure show up in the outline.
    assert!(names.contains(&"x"), "outline missing var `x`: {names:?}");
    assert!(names.contains(&"y"), "outline missing var `y`: {names:?}");
    assert!(names.contains(&"Inc"), "outline missing proc `Inc`: {names:?}");

    // The procedure nests its local parameter/declarations as children.
    let inc = syms.iter().find(|s| s["name"] == "Inc").unwrap();
    let children = inc["children"].as_array().expect("Inc should have children");
    let child_names: Vec<&str> = children.iter().filter_map(|c| c["name"].as_str()).collect();
    assert!(
        child_names.contains(&"val"),
        "Inc's children should include param `val`: {child_names:?}"
    );
}

#[test]
fn references_span_files_for_an_exported_symbol() {
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/xfile");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed");
    s.did_open(&prog_uri, &text);

    // Cursor on the imported `triple` use (line 4). Its references must reach the
    // defining unit (mylib.pas) as well as this program.
    let resp = s.request_until(
        "textDocument/references",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 4, "character": 10 },
            "context": { "includeDeclaration": true }
        }),
        |r| r.as_array().map_or(false, |a| !a.is_empty()),
    );
    let locs = resp["result"].as_array().unwrap();
    let files: std::collections::HashSet<&str> =
        locs.iter().filter_map(|l| l["uri"].as_str()).collect();

    assert!(
        files.iter().any(|u| u.ends_with("prog.pascalm")),
        "references should include the program, got: {files:?}"
    );
    assert!(
        files.iter().any(|u| u.ends_with("mylib.pas")),
        "references should reach the defining unit, got: {files:?}"
    );
}

#[test]
fn rename_spans_files_for_an_exported_symbol() {
    let dir = concat!(env!("CARGO_MANIFEST_DIR"), "/tests/fixtures/xfile");
    let root_uri = format!("file://{dir}");
    let prog_uri = format!("file://{dir}/prog.pascalm");
    let text = std::fs::read_to_string(format!("{dir}/prog.pascalm")).unwrap();

    let mut s = Server::start();
    s.initialize(Some(&root_uri));
    s.wait_log_containing("analyzed");
    s.did_open(&prog_uri, &text);

    let resp = s.request(
        "textDocument/rename",
        json!({
            "textDocument": { "uri": prog_uri },
            "position": { "line": 4, "character": 10 },
            "newName": "tripled"
        }),
    );
    let changes = resp["result"]["changes"]
        .as_object()
        .expect("rename should produce changes across files");
    let files: Vec<&str> = changes.keys().map(String::as_str).collect();

    assert!(
        files.iter().any(|u| u.ends_with("prog.pascalm")),
        "rename should edit the program, got: {files:?}"
    );
    assert!(
        files.iter().any(|u| u.ends_with("mylib.pas")),
        "rename should edit the defining unit, got: {files:?}"
    );
    // Every edit must carry the new name.
    for edits in changes.values() {
        for e in edits.as_array().unwrap() {
            assert_eq!(e["newText"], "tripled");
        }
    }
}
