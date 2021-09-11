#pragma once

#include <stdint.h>
#include "window.h"

struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    uint8_t alpha;
};

struct PixelPoint
{
    int x;
    int y;
};

struct Pixel
{
    Color color;
    PixelPoint coord;
};

struct Rectangle
{
    int x;
    int y;

    int width;
    int height;
};

class Renderer
{

private:

    SDL_Renderer* lib_renderer_;

public:
    
    Renderer() = delete;
    Renderer(Window* window, int idx, uint32_t flags);
    
    SDL_Renderer* lib_renderer() const;

    void Clear();
    void setDrawColor(const Color color);
    void Present();

    void drawPoint(const PixelPoint point);
    void drawLine(const PixelPoint point_a, const PixelPoint point_b);
    void fillRect(const Rectangle& rectangle);

    ~Renderer();
};
