#include "function.h"

Point* generateSpaceGrid()
{
    Point* points = malloc(8 * sizeof(Point));
    // linea +x
    points[0] = (Point){0, 0, 0};
    points[1] = (Point){1, 0, 0};
    // linea -x
    points[2] = (Point){0, 0, 0};
    points[3] = (Point){-1, 0, 0};
    // linea -z
    points[4] = (Point){0, 0, 0};
    points[5] = (Point){0, 0, -1};
    // linea +z
    points[6] = (Point){0, 0, 0};
    points[7] = (Point){0, 0, 1};

    return points;
}

void setupSpaceGrid(Point* points, int count) 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(Point), points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawSpaceGrid() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 8);  // 8 vertici = 4 linee
    glBindVertexArray(0);
}