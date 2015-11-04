--radiobutton.lua
local drawLib = require("render_ffi")

local RadioButton = {}
local RadioButton_mt = {
  __index = RadioButton;
}

function RadioButton.new(self, 
