#include <sine.c>

uint8_t mem[16];
int width = 4;
int height = 4;
int black = 0;
int white = 1;
int stride = 4 * sizeof(int);
int x;
int y;
int length;
char color;

//implement the set pixel and get pixel functions 
int getPixelLoc(x, y, stride)
{
    return (stride * y) + x;
}

void setPixel(x, y, color)
{
    int pixelLoc = getPixelLoc(x, y, stride); 
    //do i need to declare stride and the values of x
    //and y in setPixel if i did it globally?
    mem[pixelLoc] = color;
}

int hLine(x, y, int length, color)
{
    //using the parameters, draw a line in memory
    while(len > 0)
    {
        int pixelLoc = getPixelLoc(x, y, stride);
        mem[pixelLoc] = color;
        length --;
    }
}

void main()
{
    hLine(0, 1, 3, 0); //when this line is called a line should be drawn in memory
}
