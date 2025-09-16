#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "text_entity.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color text_color;
} Renderer;

Renderer* renderer_init(int window_width, int window_height);
void renderer_cleanup(Renderer* renderer);
void render_text_entities(const Renderer* renderer, TextEntity** entities, int count);
void renderer_clear(const Renderer* renderer);
void renderer_present(const Renderer* renderer);
void update_entity_dimensions(const Renderer* renderer, TextEntity* entity);

#endif
