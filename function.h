#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_WIDTH/2

typedef struct Point{
    int x;
    int y;
    int z;
} Point;


