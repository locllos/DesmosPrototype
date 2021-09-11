#include "hdr/display.h"
#include <stdio.h>

const size_t POINTS_COUNT = 4;

const PixelPoint points[POINTS_COUNT] = 
{
    {320, 200},
    {300, 240},
    {340, 240},
    {320, 200}
};

Color RED = {255, 0, 0, 255}; 
Color GREEN = {0, 255, 0, 255};
Color LIGHT_BLUE = {232, 244, 248, 255};
Color YELLOW = {255, 255, 0, 255};
Color LIME_GREEN = {232, 248, 236, 255};
Color BLUE = {67, 165, 198, 255};

double ANGLE_STEP = atan(1) / 6;

double functionParabola(double x)
{
    return x * x - 3 * x + 2;
}

int main()
{
    
    Display display("Privet Medved!");
    
    CoordinateSystem coord_system_a(25, 25, 500, 650, {-3, -4}, {5, 5});
    CoordinateSystem coord_system_b(550, 75, 450, 450, {-1, -1}, {3, 3});

    Vector vector(0, 0.75);
    Vector begin_point(1.5, functionParabola(1.5));

    bool quit = false;
    SDL_Event event = {};
    
    while (!quit)
    {   
        display.renderer->Clear();
        while (SDL_PollEvent(&event))
        {
            quit = event.type == SDL_QUIT;
        }
        display.drawCoordinateSystem(coord_system_a, LIGHT_BLUE, {0, 0, 0, 255});
        display.drawCoordinateFunction(coord_system_a, RED, functionParabola, 0.1);
        display.drawCoordinateSystem(coord_system_b, LIGHT_BLUE, {0, 0, 0, 255});
        display.drawCoordinateFunction(coord_system_b, RED, functionParabola, 0.05);

        display.drawVector(coord_system_b, GREEN, begin_point, vector);

        vector.Rotate(ANGLE_STEP / 50);

        display.renderer->setDrawColor(BLUE);
        display.renderer->Present();
    }
    return 0;
}