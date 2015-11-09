local io = require("io")

file = io.open("outfile.txt", "r")

local arr = {}

for line in file:lines() do
    regex = string.match(line, '0x')
    if not string.match(line, "SOMEREGEX HERE") then
        table.insert (arr, line);
    end
end

print(arr[2])

file:close()
