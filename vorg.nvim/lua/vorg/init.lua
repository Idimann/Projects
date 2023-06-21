function Get_filename()
    return string.format("%s ", vim.fn.expand("%:t"))
end

local M = {}

function M.helloWorld() print(Get_filename()) end

return M
