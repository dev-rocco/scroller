#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>

Renderer* renderer_init(int window_width, int window_height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    Renderer* renderer = malloc(sizeof(Renderer));
    if (renderer == NULL) {
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    renderer->window = SDL_CreateWindow("scroller - SDL2 Text Rendering",
                                      0,
                                      0,
                                      window_width,
                                      window_height,
                                      SDL_WINDOW_SHOWN);

    if (renderer->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        free(renderer);
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    renderer->renderer = SDL_CreateRenderer(renderer->window, -1, 
                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(renderer->window);
        free(renderer);
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }
    
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_BLEND);

    renderer->font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
    if (renderer->font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        printf("Trying alternative font path...\n");
        renderer->font = TTF_OpenFont("C:/Windows/Fonts/calibri.ttf", 32);
        if (renderer->font == NULL) {
            printf("Failed to load alternative font! SDL_ttf Error: %s\n", TTF_GetError());
            SDL_DestroyRenderer(renderer->renderer);
            SDL_DestroyWindow(renderer->window);
            free(renderer);
            TTF_Quit();
            SDL_Quit();
            return NULL;
        }
    }

    renderer->text_color.r = 255;
    renderer->text_color.g = 255;
    renderer->text_color.b = 255;
    renderer->text_color.a = 255;

    SDL_SetRenderDrawColor(renderer->renderer, 25, 25, 112, 255);

    return renderer;
}

void renderer_cleanup(Renderer* renderer) {
    if (renderer != NULL) {
        if (renderer->font != NULL) {
            TTF_CloseFont(renderer->font);
        }
        if (renderer->renderer != NULL) {
            SDL_DestroyRenderer(renderer->renderer);
        }
        if (renderer->window != NULL) {
            SDL_DestroyWindow(renderer->window);
        }
        free(renderer);
    }
    
    TTF_Quit();
    SDL_Quit();
}

void update_entity_dimensions(const Renderer* renderer, TextEntity* entity) {
    if (renderer == NULL || entity == NULL || renderer->font == NULL) {
        return;
    }
    
    int w, h;
    TTF_SizeText(renderer->font, entity->text, &w, &h);
    entity->width = w;
    entity->height = h;
}

void render_text_entities(const Renderer* renderer, TextEntity** entities, int count) {
    if (renderer == NULL || renderer->renderer == NULL || renderer->font == NULL) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (entities[i] == NULL) {
            continue;
        }
        
        if (entities[i]->width == 0 || entities[i]->height == 0) {
            update_entity_dimensions(renderer, entities[i]);
        }
        
        SDL_Surface* textSurface = TTF_RenderText_Solid(renderer->font, 
                                                       entities[i]->text, 
                                                       renderer->text_color);
        if (textSurface != NULL) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer->renderer, textSurface);
            if (textTexture != NULL) {
                SDL_Rect destRect = {
                    entities[i]->x,
                    0,
                    entities[i]->width,
                    entities[i]->height
                };
                
                SDL_RenderCopy(renderer->renderer, textTexture, NULL, &destRect);
                SDL_DestroyTexture(textTexture);
            }
            
            SDL_FreeSurface(textSurface);
        }
    }
}

void renderer_clear(const Renderer* renderer) {
    if (renderer != NULL && renderer->renderer != NULL) {
        SDL_RenderClear(renderer->renderer);
    }
}

void renderer_present(const Renderer* renderer) {
    if (renderer != NULL && renderer->renderer != NULL) {
        SDL_RenderPresent(renderer->renderer);
    }
}
