#include "text_entity.h"
#include <stdlib.h>
#include <string.h>

TextEntity* create_text_entity(const char* text, int x) {
    TextEntity* entity = malloc(sizeof(TextEntity));
    if (entity == NULL) {
        return NULL;
    }
    
    // Allocate memory for text and copy it
    entity->text = (char*)malloc(strlen(text) + 1);
    if (entity->text == NULL) {
        free(entity);
        return NULL;
    }
    strcpy(entity->text, text);
    
    entity->x = x;
    entity->width = 0;
    entity->height = 0;
    
    return entity;
}

void free_text_entity(TextEntity* entity) {
    if (entity != NULL) {
        if (entity->text != NULL) {
            free(entity->text);
        }
        free(entity);
    }
}

void update_text_entity(TextEntity* entity, int scroll_speed) {
    if (entity != NULL) {
        entity->x -= scroll_speed;
    }
}
