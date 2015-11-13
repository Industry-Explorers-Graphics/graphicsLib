--radiobutton.lua
local drawLib = require("render_ffi")

local RadioButton = {}
local RadioButton_mt = {
  __index = RadioButton;
}

function RadioButton.new(self, x, y, color, state)
  local obj = {
    x = x;
    y = y;
    radius = 5;
    color = color;
    state = state;
  }
  setmetatable(obj, RadioButton_mt)
  return obj
end 

function RadioButton.draw(self, fb)
  if self.state == 0 then 
    drawLib.drawCircleFill(fb, self.x, self.y, self.radius, self.color)
    drawLibdrawCirlceFill(fb, self.x, self.y, self.radius - 2, self.color)
  end
end

return RadioButton
