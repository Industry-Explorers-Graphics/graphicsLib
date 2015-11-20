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


function DrawingContext.init(self, fb, data)
	local obj = {
		width = fb.width;
		height = fb.height;
		data = fb.data;
		fb = fb;
		data = data;
	}
	setmetatable(obj, DrawingContext_mt)

	return obj;
end

function DrawingContext.new(self, width, height, data)
	return self:init(width, height, data)
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

return DrawingContext