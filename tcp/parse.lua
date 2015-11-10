local io = require("io")

file = io.open("outfile.txt", "r")

local tcp_tbl = {}

for line in file:lines() do
    hex = string.match(line, "0x%x")
    ip = string.match(line, "IP%s")
    if ip and not hex then
        table.insert (tcp_tbl, line);
    end
end

local tcp_array = {}
local time_obj = {}

for k,v in pairs(tcp_tbl) do
    time = string.match(v, "^%d%d:%d%d:%d%d.%d%d%d%d%d%d" )
    source_ip = string.match(v, "IP %d+.%d+.%d+.%d+")
    source_port = string.match(v, ".%d+%s>" )
    dest_ip = string.match(v, ">%s%d+.%d+.%d+.%d+" )
    dest_port = string.match(v, ".%d+: " )
    
    time_obj["time"] = time
    time_obj["source_ip"] = source_ip
    time_obj["source_port"] = source_port
    time_obj["dest_ip"] = dest_ip
    time_obj["dest_port"] = dest_port
   
    if time_obj ~= nil then 
        for k,v in pairs(tcp_tbl) do
            print(v)
        end
   end
   --table.insert(tcp_array, time_obj)
end

--[[ 
--Create a CSV String
function escapeCSV (s)
  if string.find(s, '[,"]') then
    s = '"' .. string.gsub(s, '"', '""') .. '"'
  end
  return s
end

function toCSV(table)
  local s = ""
  for _,p in ipairs(table) do  
    s = s .. "," .. escapeCSV(p)
  end
  return string.sub(s, 2)      -- remove first comma
end

local csv = toCSV(arr)
print(csv)
--]]
file:close()
