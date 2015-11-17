--slider.lua
local drawLib = require("render_ffi")
local colors = require("colors")
local bar = require("bar")
local handle = require("handle")

local Slider = {}
local Slider_mt = {
  __index = Slider;
}

function Slider.new(self, bar, handle, value, isDragging)
  local obj = {
    bar = bar;
    handle = handle;
    value = value;
    posx = handle.x * value;
    posy = handle.y;
    isDragging = isDragging;
  } 
  setmetatable(obj, Slider_mt)
  return obj
end 

function Slider.draw(self, fb)
  bar:draw(fb)
  handle:draw(fb)
end

function Slider.onMouseActivity(self, fb, event)
  return 0
end

function Slider.contains(self, x, y)
  return self.bar:contains(x, y)
end

return Slider
