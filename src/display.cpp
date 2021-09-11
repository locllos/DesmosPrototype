#include "hdr/display.h"

const double PI = 3.14159265359;
const char* DIGIT_FONT = "res/Fonts/TerminusTTF.ttf";
const size_t DEFAULT_FONT_SCALE = 2;
const double ARROW_ANGLE = PI / 12;

Display::Display(const char* title,
                 size_t x_pos, size_t y_pos, 
                 size_t width, size_t height)
{    
    window  = new Window(title, x_pos, y_pos, width, height, 0);
    renderer = new Renderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Display::drawLine(Line line)
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

        renderer->drawLine(line.point_a, line.point_b);

        thickness_factor_x *= (-1);
        thickness_factor_y *= (-1);
    }
}

void Display::drawLine(PixelPoint first_point, PixelPoint second_point, size_t thickness)
{
    drawLine({first_point, second_point, thickness});
}

void Display::drawVector(CoordinateSystem& coord_system, Color color, 
                         Vector& begin_point, Vector& vector, double arrow_factor_size)
{   
    renderer->setDrawColor(color);

    Vector first(begin_point); 

    Vector second = {begin_point.x() + vector.x(), begin_point.y() + vector.y()};

    double sina = sin(ARROW_ANGLE);
    double cosa = cos(ARROW_ANGLE);

    double delta_x = deltaX(first, second);
    double delta_y = deltaY(first, second);

    double afs = arrow_factor_size;
    Vector first_arrow_point  = {second.x() + afs * (delta_x * cosa + delta_y * sina),
                                 second.y() + afs * (delta_y * cosa - delta_x * sina)};
    
    Vector second_arrow_point = {second.x() + afs * (delta_x * cosa - delta_y * sina),
                                 second.y() + afs * (delta_y * cosa + delta_x * sina)};
    
    PixelPoint abs_first_vector_point = coord_system.getAbsCoordinatesFromRelative(first);
    PixelPoint abs_second_vector_point = coord_system.getAbsCoordinatesFromRelative(second);
    PixelPoint abs_first_arrow_point = coord_system.getAbsCoordinatesFromRelative(first_arrow_point);
    PixelPoint abs_second_arrow_point = coord_system.getAbsCoordinatesFromRelative(second_arrow_point);

    drawLine(abs_first_vector_point, abs_second_vector_point);
    drawLine(abs_second_vector_point, abs_first_arrow_point);
    drawLine(abs_second_vector_point, abs_second_arrow_point);
}

void Display::drawCoordinateStepY(CoordinateSystem& coord_system)
{
    PixelPoint y_coord_line_point_b = {coord_system.abs_origin_point().x, coord_system.area().y + coord_system.area().height};
    PixelPoint y_coord_line_point_a = {coord_system.abs_origin_point().x, coord_system.area().y};
    PixelPoint abs_origin_point = coord_system.abs_origin_point();
    
    int scale = coord_system.y_scale();
    int current_pos = abs_origin_point.y;

    while (current_pos < y_coord_line_point_b.y)
    {
        drawLine({abs_origin_point.x - 2, current_pos}, 
                 {abs_origin_point.x + 2, current_pos});
        current_pos += scale;
    }

    current_pos = abs_origin_point.y;
    while (current_pos > y_coord_line_point_a.y)
    {
        drawLine({abs_origin_point.x - 2, current_pos}, 
                 {abs_origin_point.x + 2, current_pos});
        current_pos -= scale;
    }
}

void Display::drawCoordinateStepX(CoordinateSystem& coord_system)
{
    PixelPoint x_coord_line_point_a = {coord_system.area().x, coord_system.abs_origin_point().y};
    PixelPoint x_coord_line_point_b = {coord_system.area().x + coord_system.area().width, coord_system.abs_origin_point().y};
    PixelPoint abs_origin_point = coord_system.abs_origin_point();

    int scale = coord_system.x_scale();
    int current_pos = abs_origin_point.x;

    while (current_pos < x_coord_line_point_b.x)
    {
        drawLine({current_pos + scale, abs_origin_point.y - 2}, 
                 {current_pos + scale, abs_origin_point.y + 2});
        current_pos += scale;
    }

    current_pos = abs_origin_point.x;
    while (current_pos > x_coord_line_point_a.x)
    {
        drawLine({current_pos, abs_origin_point.y - 2}, 
                 {current_pos, abs_origin_point.y + 2});
        current_pos -= scale;
    }
}

void Display::drawCoordSystemSteps(CoordinateSystem& coord_system)
{
    drawCoordinateStepY(coord_system);
    drawCoordinateStepX(coord_system);
}

void Display::drawCoordinateSystem(CoordinateSystem& coord_system, 
                                   Color background_color, Color foreground_color)
{

    Rectangle frame = {coord_system.area().x - 2, coord_system.area().y - 2,
                      coord_system.area().width + 4, coord_system.area().height + 4};

    renderer->setDrawColor({0, 0, 0, 255});
    renderer->fillRect(frame);
    
    renderer->setDrawColor(background_color);
    renderer->fillRect(coord_system.area());

    renderer->setDrawColor(foreground_color);
    

    Vector ox(deltaX(coord_system.max_coord(), coord_system.min_coord()), 0);
    Vector oy(0, deltaY(coord_system.max_coord(), coord_system.min_coord()));

    Vector lower_edge(0, coord_system.min_coord().y());
    Vector left_edge(coord_system.min_coord().x(), 0);

    drawVector(coord_system, foreground_color, lower_edge, oy, 0.05);
    drawVector(coord_system, foreground_color, left_edge, ox, 0.05);

    drawCoordSystemSteps(coord_system);
}

void Display::drawLineStep(CoordinateSystem& coord_system, 
                  PixelPoint abs_first_point, PixelPoint abs_second_point)
{
    if (coord_system.isWithinCoordSystem(abs_first_point) && 
        coord_system.isWithinCoordSystem(abs_second_point))
    {
        drawLine(abs_first_point, abs_second_point); 
    }
    else if (!coord_system.isWithinCoordSystem(abs_first_point) &&
              coord_system.isWithinCoordSystem(abs_second_point))
    {
        drawLine({abs_first_point.x, 
                  abs_first_point.y > coord_system.area().y + coord_system.area().height ?
                  coord_system.area().y + coord_system.area().height : coord_system.area().y}, 
                  abs_second_point);
    }
    else if ( coord_system.isWithinCoordSystem(abs_first_point) &&
             !coord_system.isWithinCoordSystem(abs_second_point))
    {
        drawLine(abs_first_point, {abs_second_point.x, 
                                   abs_second_point.y > coord_system.area().y + coord_system.area().height ?
                                   coord_system.area().y + coord_system.area().height : coord_system.area().y}); 
    } 
}

void Display::drawCoordinateFunction(CoordinateSystem& coord_system, Color color,  
                                     double (*function)(double), double step)
{   
    renderer->setDrawColor(color);

    Vector left_lower_coord(coord_system.min_coord().x(), coord_system.max_coord().y());
    Vector rel_first_point(coord_system.min_coord().x(), coord_system.min_coord().y());
    Vector rel_second_point(coord_system.min_coord().x() + step, coord_system.min_coord().y());

    while (rel_second_point.x() < coord_system.max_coord().x())
    {
        rel_first_point.y(function(rel_first_point.x()));
        rel_second_point.y(function(rel_second_point.x()));
        
        PixelPoint abs_first_point  = coord_system.getAbsCoordinatesFromRelative(rel_first_point);
        PixelPoint abs_second_point = coord_system.getAbsCoordinatesFromRelative(rel_second_point);

        drawLineStep(coord_system, abs_first_point, abs_second_point);
       
        rel_first_point.x(rel_second_point.x());
        rel_second_point.x(rel_second_point.x() + step);
    } 
}


Display::~Display()
{
    delete window;
    delete renderer;
}