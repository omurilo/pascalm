vim.filetype.add({
	extension = {
		pas = "pascalm",
		pascalm = "pascalm",
	},
})

vim.lsp.config("pascalmls", {
	cmd = {
		"pascalmls",
	},
	filetypes = { "pascalm", "pas" },
	root_dir = function()
		return vim.fn.getcwd()
	end,
})

vim.lsp.enable("pascalmls")
