#include "hdr/display.h"

void SDL_SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void SDL_RenderDrawLine(SDL_Renderer* renderer, SDL_Point point_a, SDL_Point point_b)
{
    SDL_RenderDrawLine(renderer, point_a.x, point_a.y, 
                                 point_b.x, point_b.y);
}

void constructDisplay(Display* display, 
                      const char* title,
                      int x_pos, int y_pos, 
                      int width, int height)
{   
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    display->window  = SDL_CreateWindow(title, x_pos, y_pos, width, height, 0);
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    display->surface = SDL_GetWindowSurface(display->window);
}

void renderScaledTexture(SDL_Texture* texture, SDL_Renderer* renderer, 
                         int coord_x, int coord_y, 
                         size_t width, size_t height)
{
    SDL_Rect rectangle_preferences = {};
    rectangle_preferences.x = coord_x;
    rectangle_preferences.y = coord_y;
    rectangle_preferences.h = height;
    rectangle_preferences.w = width;
    SDL_RenderCopy(renderer, texture, nullptr, &rectangle_preferences);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, 
                   int coord_x, int coord_y)
{
    int default_width = 0;
    int default_height = 0;

    SDL_QueryTexture(texture, 
                     nullptr, nullptr, 
                     &default_width, &default_height);

    renderScaledTexture(texture, renderer, 
                        (int)coord_x, (int)coord_y, 
                        default_width, default_height);
}

SDL_Texture* loadText(const char* message, TTF_Font* font, 
                      SDL_Color color, size_t font_size, SDL_Renderer* renderer)
{
        SDL_Surface *surface = TTF_RenderText_Blended(font, message, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);

        return texture;
}

SDL_Texture* loadTextOnce(const char* message, const char* font_filename,
                            SDL_Color color, size_t font_size, SDL_Renderer *renderer)
{
        TTF_Font *font = TTF_OpenFont(font_filename, font_size);

        SDL_Texture* texture = loadText(message, font, color, font_size, renderer);

        TTF_CloseFont(font);
        return texture;
}

void destructDisplay(Display* display)
{
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
}

Display* newDisplay(const char* title,
                    int x_pos, int y_pos,
                    int width, int height)
{
    Display* display = (Display*)calloc(1, sizeof(Display));

    constructDisplay(display, title, x_pos, y_pos, width, height);

    return display;
}

Display* deleteDisplay(Display* display)
{
    destructDisplay(display);

    free(display);

    return nullptr;
}