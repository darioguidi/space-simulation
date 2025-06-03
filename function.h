#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_WIDTH/2

extern GLuint VAO;
extern GLuint VBO;

typedef struct {
    float x, y, z;
} Point;

Point* generateSpaceGrid();
void setupSpaceGrid(Point* points, int count);
void drawSpaceGrid();


