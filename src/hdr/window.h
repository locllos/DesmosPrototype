#pragma once

#include <SDL2/SDL.h>

class Window
{
private:
 
    SDL_Window* lib_window_;

public:
    Window() = delete;
    
    Window(const char* title, 
           size_t x_pos, size_t y_pos, 
           size_t width, size_t height, uint32_t flags);
    
    SDL_Window* lib_window() const;
    void window(SDL_Window* window);
    
    ~Window();
};