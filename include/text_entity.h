#ifndef TEXT_ENTITY_H
#define TEXT_ENTITY_H

#include <SDL.h>

typedef struct {
    char* text;
    int x;
    int width;
    int height;
} TextEntity;

TextEntity* create_text_entity(const char* text, int x);
void free_text_entity(TextEntity* entity);
void update_text_entity(TextEntity* entity, int scroll_speed);

#endif
