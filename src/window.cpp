#include "hdr/window.h"

Window::Window(const char* title, 
               size_t x_pos, size_t y_pos, 
               size_t width, size_t height, uint32_t flags) 
{   
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }
    
    lib_window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
}

SDL_Window* Window::lib_window() const
{
    return lib_window_;
}

void Window::window(SDL_Window* window)
{
    lib_window_ = window;
}

Window::~Window()
{
    SDL_DestroyWindow(lib_window_);
}