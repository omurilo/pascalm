local lsp_path = vim.fn.fnamemodify(debug.getinfo(1, "S").source:sub(2), ":p:h")
local binary_path = lsp_path .. "/target/release/pascalmls"
-- 0. [Optional] create a custom log file, otherwise it will log in `~/.local/state/nvim/lsp.log`
local log_file = lsp_path .. "/pascalmls.log"

-- 1. Start LSP client
local client = vim.lsp.start_client({
	name = "pascalmls",
	cmd = { "sh", "-c", binary_path .. " 2>" .. log_file },
	filetypes = { "pascalm, pas" }, -- only for markdown, but you can add multiple patterns
	root_dir = vim.fn.getcwd(),
})

-- 2. Auto-attach to markdown buffers
vim.api.nvim_create_autocmd("FileType", {
	pattern = "pascalm|pas",
	callback = function()
		vim.lsp.buf_attach_client(vim.api.nvim_get_current_buf(), client) -- attaching the client to the current buffer
	end,
})
