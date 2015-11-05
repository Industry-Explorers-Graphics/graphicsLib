--label.lua
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
   drawLib.drawText(fb, self.x, self.y, self.text, self.color)
end

return Label
