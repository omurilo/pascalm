# pascalmls.nvim

Neovim integration for the [PascalM](../../../README.md) language server (`pascalmls`).

## What the server provides

Once attached, `pascalmls` offers (all via the standard `vim.lsp` handlers):

- **Diagnostics** — syntactic + semantic, refreshed on every change.
- **Hover** (`K`) — symbol signature/type, including symbols imported from `uses` units and the stdlib.
- **Go-to-definition** (`grd` / `vim.lsp.buf.definition`) — cross-file and into the stdlib.
- **References** (`grr`) and **rename** (`grn`) — single-file and **cross-file** for exported symbols.
- **Completion** (`<C-x><C-o>`, or wire `vim.lsp.completion.enable` / `nvim-cmp`) — local symbols, symbols exported by `used` units, and keywords.
- **Document symbols** — feeds the outline / `gO` / `:Telescope lsp_document_symbols` / aerial, etc.
- **Semantic tokens** (highlight) and **formatting** (`gq` / `vim.lsp.buf.format`).

The capabilities and their **current limitations / roadmap** are documented in the main
[project README](../../../README.md#language-server-pascalmls). In short: completion is
identifier-level (no member-access yet), and cross-file references/rename rely on the
workspace index built at startup (unsaved edits in *other* files reflect after a save).

> Completion note: Neovim's native client exposes server completion through omnifunc
> (`<C-x><C-o>`). For as-you-type popups, enable `vim.lsp.completion.enable(true, client_id, bufnr, { autotrigger = true })`
> on `LspAttach`, or use `nvim-cmp` + `cmp-nvim-lsp`.

## Setup

`setup()` does everything for you:

- registers the `pascalm`/`pas` filetypes;
- configures (`vim.lsp.config`) and enables (`vim.lsp.enable`) the `pascalmls` server;
- **auto re-attaches** `pascalmls` to open buffers after a restart. `vim.lsp.enable`
  only attaches via a FileType autocmd (new buffers only), so after a restart the
  already-open buffers stay unattached and requests like formatting hang. This is
  scoped to `pascalmls` only — it does **not** touch the global `:LspRestart`, so
  other servers behave exactly as your config already defines.

## The server binary

You don't need to install `pascalmls` yourself — the `build` step (`build.sh`)
fetches it. It **downloads a prebuilt binary** for your platform from the latest
GitHub Release into the plugin's `bin/` directory (no toolchain required). If no
release asset is available and the Rust source sits next to the plugin (in-repo
checkout), it **falls back to building from source** (needs Rust + LLVM 18).

The plugin then runs `<plugin>/bin/pascalmls` automatically, falling back to a
`pascalmls` on your `PATH` if the bundled binary isn't present.

> Publishing the assets: a release must contain binaries named
> `pascalmls-<target>` (e.g. `pascalmls-aarch64-apple-darwin`,
> `pascalmls-x86_64-unknown-linux-gnu`). See the repo's release workflow.

## Install (lazy.nvim)

Local checkout — declare it with the `build` step:

```lua
{
  dir = vim.fn.expand("~/projects/personal/pascalm/src/lsp/pascalmls.nvim"),
  build = "bash build.sh", -- download (or build) the server binary
  lazy = false,            -- load at startup so the filetype is registered
  opts = {},               -- lazy.nvim calls require("pascalmls").setup(opts)
}
```

Published to GitHub:

```lua
{ "omurilo/pascalmls.nvim", build = "bash build.sh", lazy = false, opts = {} }
```

Re-run the download/build at any time with `:Lazy build pascalmls`.

## Options

```lua
opts = {
  cmd = { "pascalmls" },   -- how to launch the server
  -- root_dir: by default the top of the contiguous Pascal source tree (climbs
  -- while the parent dir directly contains .pascalm/.pas files), which groups a
  -- program and its units under one client. To override, use the Neovim 0.11
  -- signature — CALL on_dir, don't return (a returning function never resolves
  -- and the client won't start); a string also works:
  --   root_dir = function(bufnr, on_dir) on_dir(vim.fs.root(bufnr, ".git") or vim.fn.getcwd()) end,
  -- Set `root_dir = false` for single-file mode (no root).
  server = {},             -- extra fields merged into vim.lsp.config("pascalmls", …)
  auto_reattach = true,    -- re-attach pascalmls after a restart
}
```

## Notes

- The re-attach is triggered when a `pascalmls` client detaches and the buffer
  ends up with no `pascalmls` client. It respects an explicit stop: it won't
  re-attach if the server was disabled with `vim.lsp.enable("pascalmls", false)`.
- It does not define new commands and does not override `:LspRestart`.
