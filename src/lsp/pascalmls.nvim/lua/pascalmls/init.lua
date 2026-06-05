-- pascalmls.nvim — Neovim integration for the PascalM language server.
--
-- Registers the `pascalm`/`pas` filetypes, configures and enables the
-- `pascalmls` LSP, and automatically re-attaches it to open buffers after a
-- restart. `vim.lsp.enable` only attaches via a FileType autocmd (new buffers
-- only), so after a restart the already-open buffers stay unattached and
-- requests like formatting hang — this fixes that, scoped to pascalmls only,
-- without touching the global `:LspRestart`.
--
-- Usage with lazy.nvim — just declare it, nothing else required:
--
--   {
--     dir = vim.fn.expand("~/projects/personal/pascalm/src/lsp/pascalmls.nvim"),
--     lazy = false, -- load at startup so the filetype is registered
--     opts = {},    -- lazy calls require("pascalmls").setup(opts)
--   }
--
-- Or, once published to GitHub at <user>/pascalmls.nvim:
--
--   { "omurilo/pascalmls.nvim", lazy = false, opts = {} }

local M = {}

local uv = vim.uv or vim.loop
local did_setup = false

-- Does `dir` directly contain a .pascalm/.pas file?
local function dir_has_pascal(dir)
  local ok, it = pcall(vim.fs.dir, dir)
  if not ok or not it then
    return false
  end
  for name, type_ in it do
    if type_ == "file" and (name:sub(-8) == ".pascalm" or name:sub(-4) == ".pas") then
      return true
    end
  end
  return false
end

-- Project root for a buffer: climb from the file's directory while the parent
-- still directly contains Pascal sources, so the root is the top of the
-- contiguous source tree (groups a program with its units under one client).
-- Uses the Neovim 0.11 signature: must CALL `on_dir`, not return.
local function default_root_dir(bufnr, on_dir)
  local fname = vim.api.nvim_buf_get_name(bufnr)
  if fname == "" then
    on_dir(vim.fn.getcwd())
    return
  end
  local dir = vim.fs.dirname(fname)
  while true do
    local parent = vim.fs.dirname(dir)
    if not parent or parent == dir or not dir_has_pascal(parent) then
      break
    end
    dir = parent
  end
  on_dir(dir)
end

-- Whether the pascalmls server is still meant to be running. After an explicit
-- stop (`vim.lsp.enable("pascalmls", false)`) we must NOT auto-re-attach.
local function still_enabled()
  if type(vim.lsp.is_enabled) ~= "function" then
    return true
  end
  local ok, enabled = pcall(vim.lsp.is_enabled, "pascalmls")
  return not ok or enabled
end

-- After a pascalmls client detaches (e.g. on restart), re-attach the buffer if
-- nothing brought it back. Re-emitting FileType re-triggers `vim.lsp.enable`'s
-- own auto-attach, starting a fresh client for the buffer.
local function setup_auto_reattach()
  local group = vim.api.nvim_create_augroup("PascalmlsReattach", { clear = true })
  local last = {}

  vim.api.nvim_create_autocmd("LspDetach", {
    group = group,
    callback = function(args)
      local client = vim.lsp.get_client_by_id(args.data.client_id)
      if not client or client.name ~= "pascalmls" then
        return
      end
      local buf = args.buf

      -- Wait a tick: if the restart re-attaches on its own, do nothing.
      vim.defer_fn(function()
        if not vim.api.nvim_buf_is_loaded(buf) or not still_enabled() then
          return
        end
        local attached = vim.lsp.get_clients({ bufnr = buf, name = "pascalmls" })
        if not vim.tbl_isempty(attached) then
          return
        end
        -- Debounce so a server that crashes on start can't spin a tight loop.
        local now = uv.now()
        if last[buf] and (now - last[buf]) < 2000 then
          return
        end
        last[buf] = now
        vim.api.nvim_exec_autocmds("FileType", { buffer = buf, modeline = false })
      end, 200)
    end,
  })
end

--- Set up the PascalM Neovim integration.
--- @param opts table|nil
---   opts.cmd           table     command to launch the server (default { "pascalmls" })
---   opts.root_dir      function  root_dir resolver (default: current working directory)
---   opts.server        table     extra fields merged into vim.lsp.config("pascalmls", …)
---   opts.auto_reattach boolean   auto re-attach pascalmls after a restart (default true)
function M.setup(opts)
  if did_setup then
    return
  end
  did_setup = true
  opts = opts or {}

  vim.filetype.add({
    extension = {
      pas = "pascalm",
      pascalm = "pascalm",
    },
  })

  local config = {
    cmd = opts.cmd or { "pascalmls" },
    filetypes = { "pascalm", "pas" },
  }
  -- `root_dir` follows the Neovim 0.11 signature `root_dir(bufnr, on_dir)` —
  -- you must CALL `on_dir(path)`, not return (a returning function never
  -- resolves and the client won't start). Default: the top of the Pascal source
  -- tree. Pass `opts.root_dir = false` to omit it (single-file mode).
  if opts.root_dir == nil then
    config.root_dir = default_root_dir
  elseif opts.root_dir ~= false then
    config.root_dir = opts.root_dir
  end

  vim.lsp.config("pascalmls", vim.tbl_deep_extend("force", config, opts.server or {}))

  vim.lsp.enable("pascalmls")

  if opts.auto_reattach ~= false then
    setup_auto_reattach()
  end
end

return M
