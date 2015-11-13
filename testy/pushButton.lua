--pushButton.lua
local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local lbl = require( "label" )

local ButtonBckgrnd = {}
local ButtonBckgrnd_mt = {
    __index = ButtonBackground;
}

local ButtonLabel = {}
local ButtonLabel_mt = {
    __index = ButtonLabel;
}

local PushButton = {}
local PushButton_mt = {
    __index = PushButton;
}

function ButtonBackground.new( self, x, y, color, state )
    local obj = {
        x = x;
        y = y;
        width = 5; 
        length = 20;
        color = color;
        state = state;
    }
    setmetatable( obj, ButtonBackground_mt )
    
    return obj
end

--create a bounding box to hold any type of button label
function ButtonLabel.new( self, x, y, width, length, color, children )
    local obj = {
        x = x;
        y = y;
        width = width;
        length = length;
        color = color;
        children = children
    }
    setmetatable( obj, ButtonLabel_mt )
    
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
    drawLib.drawRectFill(fb, self.x, self.y, self.width, self.length, self.color)
end

function ButtonLabel.draw( self, fb )
    drawLib.drawRectFrame(fb, self.length, self.width, self.x, self.y, self.color)
end

function PushButton.draw(self, fb)
    if self.state == 0 then
        local bckgrd = ButtonBackground:new( 300, 200, colors.GREEN, 0 )
        local label = ButtonLabel:new( colors.GREEN, { lbl:new( 0, 0, "OK", colors.WHITE )} )

        bckgrd.draw(fb)
        bckgrd.draw(fb)
    else 
        print( "there are currently no IO events" )
    end
end

return PushButton 
