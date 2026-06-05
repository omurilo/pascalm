# pascalmls.nvim

Neovim integration for the [PascalM](../../../README.md) language server (`pascalmls`).

`setup()` does everything for you:

- registers the `pascalm`/`pas` filetypes;
- configures (`vim.lsp.config`) and enables (`vim.lsp.enable`) the `pascalmls` server;
- **auto re-attaches** `pascalmls` to open buffers after a restart. `vim.lsp.enable`
  only attaches via a FileType autocmd (new buffers only), so after a restart the
  already-open buffers stay unattached and requests like formatting hang. This is
  scoped to `pascalmls` only — it does **not** touch the global `:LspRestart`, so
  other servers behave exactly as your config already defines.

## Requirements

The `pascalmls` binary must be on your `PATH`:

```bash
cd src/lsp
cargo install --path .   # or: cargo build && cp target/debug/pascalmls ~/.cargo/bin/
```

## Install (lazy.nvim)

Local checkout — just declare it, nothing else needed:

```lua
{
  dir = vim.fn.expand("~/projects/personal/pascalm/src/lsp/pascalmls.nvim"),
  lazy = false, -- load at startup so the filetype is registered
  opts = {},    -- lazy.nvim calls require("pascalmls").setup(opts)
}
```

Published to GitHub:

```lua
{ "omurilo/pascalmls.nvim", lazy = false, opts = {} }
```

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
