--label.lua
local ffi = require("ffi")
local drawLib = require("render_ffi")

local Label = {}
local Label_mt = {
  __index = Label;
}
 
function Label.new(self, x, y, text, color)
  local obj = {
    x = x;
    y = y;
    text = text;
    color = color;
  }
  setmetatable(obj, Label_mt)
  
  return obj
end

function Label.draw(self, fb)
   local text = self.text
   local c_string = ffi.new("char[?]", #text)
   ffi.copy(c_str, text)
   drawLib.drawText(fb, self.x, self.y, c_string, self.color)
end

return Label
