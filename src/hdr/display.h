#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Display
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

};


void SDL_SetRenderDrawColor (SDL_Renderer* renderer, SDL_Color color);
void SDL_RenderDrawLine     (SDL_Renderer* renderer, SDL_Point point_a, SDL_Point point_b);

SDL_Texture* loadTextOnce (const char* message, const char* font_filename,
                           SDL_Color color, size_t font_size, SDL_Renderer *renderer);
void         renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, 
                           int coord_x, int coord_y);

void constructDisplay       (Display* display,   
                             const char* title, 
                             int x_pos =  SDL_WINDOWPOS_CENTERED, int y_pos =  SDL_WINDOWPOS_CENTERED,
                             int width = 1024, int height = 768);
                      
void destructDisplay        (Display* display);

Display* newDisplay         (const char* title,
                             int x_pos =  SDL_WINDOWPOS_CENTERED, int y_pos =  SDL_WINDOWPOS_CENTERED,
                             int width = 1024, int height = 768);

Display* deleteDisplay      (Display* display);

#endif 