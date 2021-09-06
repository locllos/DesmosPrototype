#include "hdr/draw.h"
#include "hdr/service.h"

const double PI = 3.14159265359;
const char* DIGIT_FONT = "res/Fonts/TerminusTTF.ttf";
const size_t DEFAULT_FONT_SCALE = 2;
const double ARROW_ANGLE = PI / 12;

void drawDot(Display* display, CoordinateSystem* coord_system, SDL_Color color, Point point)
{
    SDL_Point abs_point = getAbsCoordinatesFromRelative(coord_system, point);
    SDL_Rect dot = {abs_point.x - 1, abs_point.y - 1, 3, 3};
    
    SDL_RenderFillRect(display->renderer, &dot);
}

void drawLine(Display* display, Line line)
{   
    size_t thickness_factor_y = 0;
    size_t thickness_factor_x = 0;

    if ((line.point_a.x - line.point_b.x) * (line.point_a.x - line.point_b.x) >
        (line.point_a.y - line.point_b.y) * (line.point_a.y - line.point_b.y))
    {
        thickness_factor_y = 1;
    }
    else
    {
        thickness_factor_x = 1;
    }

    for (size_t i = 0; i < line.thickness; ++i)
    {   
        line.point_a.x = fabs(line.point_a.x + thickness_factor_x * i);
        line.point_b.x = fabs(line.point_b.x + thickness_factor_x * i);
        line.point_a.y = fabs(line.point_a.y + thickness_factor_y * i);
        line.point_b.y = fabs(line.point_b.y + thickness_factor_y * i);

        SDL_RenderDrawLine(display->renderer, line.point_a, line.point_b);

        thickness_factor_x *= (-1);
        thickness_factor_y *= (-1);
    }
}

void drawLine(Display* display, 
              SDL_Point first_point, SDL_Point second_point, 
              size_t thickness)
{
    drawLine(display, {first_point, second_point, thickness});
}

void drawVector(Display* display, CoordinateSystem* coord_system, SDL_Color color, 
                Point begin_point, Vector vector, double arrow_factor_size)
{   
    SDL_SetRenderDrawColor(display->renderer, color);

    Point first = begin_point;
    Point second = {begin_point.x + vector.x_component, begin_point.y + vector.y_component};

    // Arrow Factor Size, просто чтобы формула не была слишком длинной
    double afs = arrow_factor_size;
    Point first_arrow_point  = { second.x + afs * ((first.x - second.x) * cos(ARROW_ANGLE) + 
                                                   (first.y - second.y) * sin(ARROW_ANGLE)),
                                 second.y + afs * ((first.y - second.y) * cos(ARROW_ANGLE) - 
                                                   (first.x - second.x) * sin(ARROW_ANGLE))};
    
    Point second_arrow_point = { second.x + afs * ((first.x - second.x) * cos(ARROW_ANGLE) -
                                                   (first.y - second.y) * sin(ARROW_ANGLE)),
                                 second.y + afs * ((first.y - second.y) * cos(ARROW_ANGLE) + 
                                                   (first.x - second.x) * sin(ARROW_ANGLE))};
    
    SDL_Point abs_first_vector_point = getAbsCoordinatesFromRelative(coord_system, first);
    SDL_Point abs_second_vector_point = getAbsCoordinatesFromRelative(coord_system, second);
    SDL_Point abs_first_arrow_point = getAbsCoordinatesFromRelative(coord_system, first_arrow_point);
    SDL_Point abs_second_arrow_point = getAbsCoordinatesFromRelative(coord_system, second_arrow_point);

    drawLine(display, abs_first_vector_point, abs_second_vector_point);
    drawLine(display, abs_second_vector_point, abs_first_arrow_point);
    drawLine(display, abs_second_vector_point, abs_second_arrow_point);
}

void drawCoordinateStepY(Display* display, CoordinateSystem* coord_system)
{
    SDL_Point y_coord_line_point_b = {coord_system->abs_origin_point.x, coord_system->area.y + coord_system->area.h};
    SDL_Point y_coord_line_point_a = {coord_system->abs_origin_point.x, coord_system->area.y};
    SDL_Point abs_origin_point = coord_system->abs_origin_point;
    
    int scale = coord_system->y_scale;
    int current_pos = abs_origin_point.y;

    while (current_pos < y_coord_line_point_b.y)
    {
        drawLine(display, {abs_origin_point.x - 2, current_pos}, 
                          {abs_origin_point.x + 2, current_pos});
        current_pos += scale;
    }

    current_pos = abs_origin_point.y;
    while (current_pos > y_coord_line_point_a.y)
    {
        drawLine(display, {abs_origin_point.x - 2, current_pos}, 
                          {abs_origin_point.x + 2, current_pos});
        current_pos -= scale;
    }


}

void drawCoordinateStepX(Display* display, CoordinateSystem* coord_system)
{
    SDL_Point x_coord_line_point_a = {coord_system->area.x, coord_system->abs_origin_point.y};
    SDL_Point x_coord_line_point_b = {coord_system->area.x + coord_system->area.w, coord_system->abs_origin_point.y};
    SDL_Point abs_origin_point = coord_system->abs_origin_point;

    int scale = coord_system->x_scale;
    int current_pos = abs_origin_point.x;

    while (current_pos < x_coord_line_point_b.x)
    {
        drawLine(display, {current_pos + scale, abs_origin_point.y - 2}, 
                          {current_pos + scale, abs_origin_point.y + 2});
        current_pos += scale;
    }

    current_pos = abs_origin_point.x;
    while (current_pos > x_coord_line_point_a.x)
    {
        drawLine(display, {current_pos, abs_origin_point.y - 2}, 
                          {current_pos, abs_origin_point.y + 2});
        current_pos -= scale;
    }
}

void drawCoordSystemSteps(Display* display, CoordinateSystem* coord_system)
{
    drawCoordinateStepY(display, coord_system);
    drawCoordinateStepX(display, coord_system);
}

void drawCoordinateSystem(Display* display, CoordinateSystem* coord_system, 
                          SDL_Color background_color, SDL_Color foreground_color)
{
    SDL_SetRenderDrawColor(display->renderer, background_color);

    SDL_RenderFillRect(display->renderer, &coord_system->area);

    SDL_SetRenderDrawColor(display->renderer, foreground_color);
    

    Vector ox = {coord_system->max_coord.x - coord_system->min_coord.x, 0};
    Vector oy = {0, coord_system->max_coord.y - coord_system->min_coord.y};

    drawVector(display, coord_system, foreground_color, {0, (double)coord_system->min_coord.y}, oy, 0.05);
    drawVector(display, coord_system, foreground_color, {(double)coord_system->min_coord.x, 0}, ox, 0.05);

    drawCoordSystemSteps(display, coord_system);
}

void drawLineStep(Display* display, CoordinateSystem* coord_system, 
                  SDL_Point abs_first_point, SDL_Point abs_second_point)
{
    if (isWithinCoordSystem(coord_system, abs_first_point) && 
        isWithinCoordSystem(coord_system, abs_second_point))
    {
        drawLine(display, abs_first_point, abs_second_point); 
    }
    else if (!isWithinCoordSystem(coord_system, abs_first_point) &&
              isWithinCoordSystem(coord_system, abs_second_point))
    {
        drawLine(display, {abs_first_point.x, 
                           abs_first_point.y > coord_system->area.y + coord_system->area.h ?
                           coord_system->area.y + coord_system->area.h : coord_system->area.y}, 
                           abs_second_point);
    }
    else if (isWithinCoordSystem(coord_system, abs_first_point) &&
             !isWithinCoordSystem(coord_system, abs_second_point))
    {
        drawLine(display, abs_first_point, {abs_second_point.x, 
                                            abs_second_point.y > coord_system->area.y + coord_system->area.h ?
                                            coord_system->area.y + coord_system->area.h : coord_system->area.y}); 
    } 
}

void drawCoordinateFunction(Display* display, CoordinateSystem* coord_system, SDL_Color color,  
                            double (*function)(double), double step)
{   
    SDL_SetRenderDrawColor(display->renderer, color);

    Point left_lower_coord  = {coord_system->min_coord.x, coord_system->max_coord.y};
    Point rel_first_point   = {coord_system->min_coord.x, coord_system->min_coord.y};
    Point rel_second_point  = {coord_system->min_coord.x + step, coord_system->min_coord.y};

    while (rel_second_point.x < coord_system->max_coord.x)
    {
        rel_first_point.y  = function(rel_first_point.x);
        rel_second_point.y = function(rel_second_point.x);
        
        SDL_Point abs_first_point  = getAbsCoordinatesFromRelative(coord_system, rel_first_point);
        SDL_Point abs_second_point = getAbsCoordinatesFromRelative(coord_system, rel_second_point);

        drawLineStep(display, coord_system, abs_first_point, abs_second_point);
       
        rel_first_point.x = rel_second_point.x;
        rel_second_point.x += step;
    } 
}










