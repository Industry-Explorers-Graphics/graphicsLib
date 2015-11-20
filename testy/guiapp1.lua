--guiapp1.lua
--package.path = package.path..";../?.lua"

local render = require("render_ffi")
local gap = require("GuiApplication")
local DrawingContext = require("DrawingContext")
local colors = require("colors")

local awidth = 640;
local aheight = 480;

local dc = nil;
local fb = nil;

--[[
	Mouse Activity functions.  Implement whichever
	ones of these are appropriate for your application.

	It is ok to not implement them as well, if your
	application doesn't require any mouse activity.
--]]
function mousePressed()
	print("mousePressed(): ", mouseButton)
end

function mouseReleased()
	print("mouseReleased(): ", mouseButton)
end

function mouseDragged()
	print("mouse drag: ", mouseX, mouseY)
end

function mouseMoved()
	print("mouse move: ", mouseX, mouseY)
end

--[[
	Keyboard Activity functions.

	Implement as many of these as your application needs.
--]]
function keyPressed()
	print("keyPressed(): ", keyCode)
end

function keyReleased()
	print("keyReleased(): ", keyCode)
end




function setup()
	print("setup")
	local data = gap.size(awidth,aheight)
	fb = render.createFrameBuffer (awidth, aheight, 0, 0, data, awidth )
	dc = DrawingContext(fb, data)
end

local count = 1;

function loop()
	--print("loop: ", count)
	count = count + 1;
	dc:setPixel(10, 10, colors.WHITE)

	dc:hline(10, 20, 100, colors.WHITE)

	dc:rect(10, 30, 100, 100, colors.RED)
	dc:rect(110, 30, 100, 100, colors.GREEN)
	dc:rect(210, 30, 100, 100, colors.BLUE)
end


gap.run()
