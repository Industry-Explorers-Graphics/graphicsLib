
local ffi = require("ffi")
require("render_ffi")
local pixel = ffi.typeof("pixel")

return {
    PINK = pixel { 240, 54, 87};
    RED = pixel { 250, 0, 0};
    ORANGE = pixel { 255, 122, 0};
    YELLOW = pixel { 255, 211, 0};
    GREEN = pixel { 0, 250, 0};
    BLUE = pixel { 0, 0, 250};
    PURPLE = pixel { 119, 3, 173};
    WHITE = pixel { 255, 255, 255};
    BLACK = pixel { 0, 0, 0};
}
