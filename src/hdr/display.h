#pragma once

#include "coordinate_system.h"

const double ARROW_FACTOR_SIZE = 0.1;

struct Line
{
    PixelPoint point_a;
    PixelPoint point_b;

    size_t thickness;
};

class Display
{
private:


    void drawCoordinateStepX(CoordinateSystem& coord_system);
    void drawCoordinateStepY(CoordinateSystem& coord_system);
    void drawCoordSystemSteps(CoordinateSystem& coord_system);
    void drawLineStep(CoordinateSystem& coord_system, 
                      PixelPoint abs_first_point, PixelPoint abs_second_point);

public:
    
    Window* window;
    Renderer* renderer;

public:

    Display() = delete;
    
    Display(const char* title, 
            size_t x_pos =  SDL_WINDOWPOS_CENTERED, size_t y_pos =  SDL_WINDOWPOS_CENTERED,
            size_t width = 1024, size_t height = 768);

    void drawLine(Line line);
    void drawLine(PixelPoint point_a, PixelPoint point_b, size_t thickness = 1);
    void drawVector(CoordinateSystem& coord_system, Color color, 
                    Vector& begin_point, Vector& vector, double arrow_factor_size = ARROW_FACTOR_SIZE);
    void drawCoordinateSystem(CoordinateSystem& coord_system, 
                              Color background_color, Color foreground_color);
    void drawCoordinateFunction(CoordinateSystem& coord_system, Color color, 
                                double (*function)(double), double step);


    ~Display();

};