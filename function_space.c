#include "function.h"

Point* generateSpaceGrid()
{
    Point* points = malloc(8 * sizeof(Point));
    // Asse X positivo
    points[0] = (Point){0, 0, 0};
    points[1] = (Point){1, 0, 0};
    // Asse X negativo
    points[2] = (Point){0, 0, 0};
    points[3] = (Point){-1, 0, 0};
    // Asse Z positivo
    points[4] = (Point){0, 0, 0};
    points[5] = (Point){0, 0, 1};
    // Asse Z negativo
    points[6] = (Point){0, 0, 0};
    points[7] = (Point){0, 0, -1};

    return points;
}

void drawSpaceGrid() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 8);  // 8 vertici = 4 linee
    glBindVertexArray(0);
}