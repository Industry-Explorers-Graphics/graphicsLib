--pushButton.lua
local ffi = require( "ffi" )
local drawLib = require( "render_ffi" )
local mouseEvent = require( "mouseActivity" );
local colors = require( "colors" );

local PushButton = {}
local PushButton_mt = {
    __index = PushButton;
}


-- need to implement children.length
function PushButton.new( self, x, y, length, color, children, state )
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
    setmetatable( obj, PushButton_mt )

    return obj
end

function PushButton.draw( self, fb, mouseEvent )
    if not PushButton:isMousePressed() then
        drawLib.drawRectFill( fb, self.x, self.y, self.width, self.length, colors.BLUE )
    else
        drawLib.drawRectFill( fb, self.x, self.y, self.width, self.length, colors.PURPLE )
    end
    if self.children ~= nil then
        for _,child in ipairs( self.children ) do
        child:draw( fb )
        end
    end
end

function PushButton.contains( self, x, y )
    if x >= self.x and x <= self.x + self.width and y >= self.y and y <= self.y + self.length then
    return true
  else
    return false
  end
end

function PushButton.isMousePressed( self, mouseEvent )
    if mouseEvent.ButtonActivity.LeftButtonDown == 1 and PushButton:Contains( mouseEvent.X, mouseEvent.Y) then
        return true
    else
        return false
    end
end

return PushButton
