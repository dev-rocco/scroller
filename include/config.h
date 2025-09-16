#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>

#define MAX_SENTENCES 50
#define MAX_SENTENCE_LENGTH 256

typedef struct {
    int window_width;
    int window_height;
    int scroll_speed;
    int spacing;
    SDL_Color text_color;
    char font_path[256];
    int font_size;
    char sentences[MAX_SENTENCES][MAX_SENTENCE_LENGTH];
    int sentence_count;
} AppConfig;

// Function declarations
AppConfig* load_config(const char* filename);
void free_config(AppConfig* config);
int parse_config_file(const char* filename, AppConfig* config);

#endif
