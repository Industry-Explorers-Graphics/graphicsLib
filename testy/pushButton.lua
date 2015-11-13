--pushButton.lua

--[[
  Specs:
    1.Button should have width of x and length of y,
      where x is:
      and y is:
    2.Bounding box should be at least 4px smaller in
      length and width of the button's borders and 'centered'
    3.Label is a child of bounding box and should be
      constrained w/in bounding box and 'centered'
]]

local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )

local ButtonBackground = {}
local ButtonBackground_mt = {
    __index = ButtonBackground;
}

local LabelBox = {}
local LabelBox_mt = {
    __index = LabelBox;
}

local PushButton = {}
local PushButton_mt = {
    __index = PushButton;
}

function ButtonBackground.new( self, x, y, color )
    local obj = {
        x = x;
        y = y;
        width = 10;
        length = 20;
        color = color;
        state = state;
    }
    setmetatable( obj, ButtonBackground_mt )

    return obj
end

--create a bounding box to hold any type of button label
function LabelBox.new( self, x, y, width, length, color, children )
    local obj = {
        x = x;
        y = y;
        width = 6;
        length = 16;
        color = color;
        children = children;
    }
    setmetatable( obj, LabelBox_mt )

    return obj
end

function PushButton.new( self, x, y, width, length, color )
    local obj = {
        x = x;
        y = y;
        width = width;
        length = length;
        color = color;
    }
    setmetatable( obj, PushButton_mt )

    return obj
end

function ButtonBackground.draw( self, fb )
    drawLib.drawRectFill( fb, self.x, self.y, self.width, self.length, self.color )
end

function LabelBox.draw( self, fb )
    drawLib.drawRectFrame( fb, self.length, self.width, self.x, self.y, self.color )
end

function PushButton.draw(self, fb)
    if self.state == 0 then
        local bckgrd = ButtonBackground:new( 300, 200, colors.GREEN, 0 )
        --for now, automatically give the button a text label child
        local label = LabelBox:new( bckgrd.x - 2, bckgrd.y - 2, width, length, colors.GREEN, { lbl:new( 0, 0, "OK", colors.WHITE )} )

        bckgrd.draw(fb)
        label.draw(fb)
    else
        print( "there are currently no IO events" )
    end
end

return PushButton
