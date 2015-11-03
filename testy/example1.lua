local scene = require( "sample" )
local ppm = require( "ppm" )
local ffi = require( "ffi" )
local fb = createFrameBuffer( 500, 600, 0, 0, 0, 500 )

for _, element in ipairs ( scene ) do
    element:Draw( fb )
end

ppm.write_PPM_binary( "example1.ppm", fb )
