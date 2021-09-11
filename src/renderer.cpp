#include "hdr/renderer.h"

Renderer::Renderer(Window* window, int idx, uint32_t flags)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    lib_renderer_ = SDL_CreateRenderer(window->lib_window(), idx, flags);
}

SDL_Renderer* Renderer::lib_renderer() const
{
    return lib_renderer_;
}

void Renderer::Clear() 
{
    SDL_RenderClear(lib_renderer_);
}

void Renderer::setDrawColor(const Color color)
{
    SDL_SetRenderDrawColor(lib_renderer_, color.red, color.green, color.blue, color.alpha);
}

void Renderer::Present()
{
    SDL_RenderPresent(lib_renderer_);
}

void Renderer::drawPoint(const PixelPoint point)
{
    SDL_RenderDrawPoint(lib_renderer_, point.x, point.y);
}

void Renderer::drawLine(const PixelPoint point_a, const PixelPoint point_b)
{
    SDL_RenderDrawLine(lib_renderer_, point_a.x, point_a.y, point_b.x, point_b.y);
}

void Renderer::fillRect(const Rectangle& rectangle)
{   
    SDL_Rect sdl_rectangle = {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
    
    SDL_RenderFillRect(lib_renderer_, &sdl_rectangle);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(lib_renderer_);
}

