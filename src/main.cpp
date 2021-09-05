#include "hdr/draw.h"
#include <stdio.h>

const size_t POINTS_COUNT = 4;

const SDL_Point points[POINTS_COUNT] = 
{
    {320, 200},
    {300, 240},
    {340, 240},
    {320, 200}
};

SDL_Color RED = {255, 0, 0, 255}; 
SDL_Color GREEN = {0, 255, 0, 255};

double functionParabola(double x)
{
    return x * x - 3 * x + 2;
}

int main()
{
    
    Display* display = newDisplay("Privet Medved!");
    
    CoordinateSystem* coord_system_a = newCoordinateSystem(25, 25, 400, 400, {200, 200}, 25);
    drawCoordinateSystem(display, coord_system_a, {255, 255, 255, 255}, {0, 0, 0, 255});
    drawCoordinateFunction(display, coord_system_a, RED, functionParabola, 0.1);

    CoordinateSystem* coord_system_b = newCoordinateSystem(450, 25, 300, 300, {25, 200}, 100);
    drawCoordinateSystem(display, coord_system_b, {255, 255, 255, 255}, {0, 0, 0, 255});
    drawCoordinateFunction(display, coord_system_b, RED, functionParabola, 0.05);

    Vector vector_a = {1, 1};
    Vector vector_b = {0, 1.5};
    Point begin_point_a = {0.5, 0.5};
    Point begin_point_b = {1.5, functionParabola(1.5)};
    drawVector(display, coord_system_a, GREEN, begin_point_a, vector_a);
    drawVector(display, coord_system_b, GREEN, begin_point_a, vector_a);
    drawVector(display, coord_system_b, GREEN, begin_point_b, vector_b);

    SDL_RenderPresent(display->renderer);

    bool quit = false;
    SDL_Event event = {};
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            quit = event.type == SDL_QUIT;
        }
    }
    display = deleteDisplay(display);

    return 0;
}