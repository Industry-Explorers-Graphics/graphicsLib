local sample = require( "sample" )
local ffi = require( "ffi" )

local text = [ sample.boundingBox[ 1 ][ 1 ] ]
local function RGB( r, g, b )
    local band, bor
    return band( 0XFFFFFF, bor( lshift( r, 16 ), lshift( g, 8 ), b ) )

local Box.Draw(self, fb)
{
    local color = RGB()
    local color2 = RGB()
    local width =
    local length = 

    drawRectFrame( fb, length, width, x, y, color )
    drawText( fb, px, py, text, color2 )
    
    for _, child in ipairs( children ) do
        child:Draw( fb );
    end
}
