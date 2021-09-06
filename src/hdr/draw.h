#include "coordinate_system.h"
#include "display.h"
#include "line.h"

const double ARROW_FACTOR_SIZE = 0.1;


void drawDot(Display* display, CoordinateSystem* coord_system, SDL_Color color, Point point);
void drawLine(Display* display, Line line);
void drawLine(Display* display, SDL_Point point_a, SDL_Point point_b, size_t thickness = 1);
void drawVector(Display* display, CoordinateSystem* coord_system, SDL_Color color, 
                Point begin_point, Vector vector, double arrow_factor_size = ARROW_FACTOR_SIZE);
void drawCoordSystemSteps(Display* display, CoordinateSystem* coord_system, SDL_Color color);
void drawCoordinateSystem(Display* display, CoordinateSystem* coord_system, 
                          SDL_Color background_color, SDL_Color foreground_color);
void drawCoordinateFunction(Display* display, CoordinateSystem* coord_system, SDL_Color color, 
                            double (*function)(double), double step);
