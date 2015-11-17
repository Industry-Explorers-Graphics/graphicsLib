--pushButton.lua
local ffi = require("ffi")
local drawLib = require("render_ffi")

local PushButton = {}
local PushButton_mt = {
    __index = PushButton;
}


-- need to implement children.length
function PushButton.new(self, x, y, length, color, children, state)
    children = children or {}
    local obj = {
        x = x;
        y = y;
        length = length;
        color = color;
        children =  children;
        width = children[1].length or 20;
        state = 0;
    }
    setmetatable(obj, PushButton_mt)

    return obj
end

function PushButton.draw(self, fb)
  drawLib.drawRectFill(fb, self.x, self.y, self.width, self.length, self.color)
  if self.children ~= nil then
    for _,child in ipairs(self.children) do
      child:draw(fb)
    end
  end
end

function PushButton.contains(self, x, y)
    if x >= self.x and x <= self.x + self.width and y >= self.y and y <= self.y + self.length then
    return true
  else
    return false
  end
end

return PushButton
