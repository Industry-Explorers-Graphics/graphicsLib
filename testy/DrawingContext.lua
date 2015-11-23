local ffi = require("ffi")
local render = require("render_ffi")

local DrawingContext = {}
setmetatable(DrawingContext, {
	__call = function(self, ...)
		return self:new(...)
	end,
})
local DrawingContext_mt = {
	__index = DrawingContext;
}


function DrawingContext.init(self, fb)
	local obj = {
		width = fb.width;
		height = fb.height;
		data = fb.data;
		fb = fb;
        nX = 10;
        nY = 30;

	}
	setmetatable(obj, DrawingContext_mt)

	return obj;
end

function DrawingContext.new(self, width, height, data)
    local fb = render.createFrameBuffer( width, height, 0, 0, data, width ) 
	return self:init(fb)
end



function DrawingContext.setPixel(self, x, y, value)
	local offset = y*self.width+x;
	self.fb.data[offset] = value;
end

function DrawingContext.hline(self, x, y, length, value)
	render.drawHorizontalLine( self.fb, length, x, y, ffi.cast("pixel",value) );
end

function DrawingContext.rect(self, x, y, awidth, aheight, value)
	render.drawRectFill( self.fb, x, y, awidth, aheight, ffi.cast("pixel", value) );
end

function DrawingContext.rectBorder( self, x, y, awidth, aheight, value )
    render.drawRectFill( self.fb, x-1, y-1, awidth+1, aheight+1, value )
end

function DrawingContext.contains( self, x, y )
    if x >= self.nX and x <= self.nX + self.width and y >= self.nY and y <= self.nY + self.height then
        return true

    else
       return false
    end
end
return DrawingContext
