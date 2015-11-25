#!/usr/bin/env luajit

--guiapp2.lua
package.path = package.path..";../?.lua"


--[[
	Test using the GuiApp concept, whereby the interactor
	is a pluggable component.
--]]
local gap = require("GuiApp")
local colors = require("colors")

local awidth = 640;
local aheight = 480;

local dc = nil;

--[[
	Mouse Activity functions.  Implement whichever
	ones of these are appropriate for your application.

	It is ok to not implement them as well, if your
	application doesn't require any mouse activity.
--]]
function mousePressed()
    if mouseButton == 1 and dc:contains( mouseX, mouseY ) then
        --print( "Thank you for selecting" )
       return true
    else
        --print( "Please click inside of rectangle" )
        return false
    end
end

function mouseReleased()
    if mousePressed() then
        print( "I'm free!" )  
        sleep(.1) 
        mouseButton = 0
    return true
    end
end

function mouseDragged()
end

function mouseMoved()
end

--[[
	Keyboard Activity functions.

	Implement as many of these as your application needs.
--]]
function keyPressed()
end

function keyReleased()
end

function keyTyped(achar)
	--print("keyTyped: ", achar)

	if keyChar ~= nil then
		print(keyChar);
	end
end

-- A setup function isn't strictly required, but 
-- you MUST at least call gap.size(), or no window
-- will be created.
function setup()
	print("setup")
	dc = size(awidth,aheight)
end

local count = 1;

-- the loop function will be called every time through the 
-- event loop, regardless of any frame rate.  This might be
-- fine when you don't mind stalling the loop, and you don't
-- particularly care about frame rate.
function loop()
	--print("loop: ", count)
	count = count + 1;
    
    dc:rect( 0, 0, 640, 480, colors.BLACK )
    dc:rect(10, 30, 100, 30, colors.RED )
    --dc:text( 45, 35, "OK", colors.WHITE ) 

    
    if mousePressed() then
	    dc:rectBorder( 10, 30, 100, 30, colors.GREEN )
        dc:rect(10, 30, 100, 30, colors.PURPLE )
        --dc:text( 45, 35, "OK", colors.WHITE )
    end
end
 
--will not work in Windows
function sleep(n)
  os.execute("sleep " .. tonumber(n))
end

local function tick()
	local count = 1
	
	while true do
		print("tick: ", count)
		count = count + 1;
		yield();
	end
end

--spawn(tick)

run()
