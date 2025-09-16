#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple .ini parser helper functions
static void trim_whitespace(char* str) {
    const char* start = str;
    char* end = str + strlen(str) - 1;
    
    // Trim from start
    while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
        start++;
    }
    
    // Trim from end
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
        end--;
    }
    
    // Null terminate
    *(end + 1) = '\0';
    
    // Move trimmed string to beginning
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

static int parse_ini_line(const char* line, char* key, char* value) {
    // Skip comments and empty lines
    if (line[0] == '#' || line[0] == ';' || line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
        return 0;
    }
    
    // Find equals sign
    char* equals = strchr(line, '=');
    if (equals == NULL) {
        return 0;
    }
    
    // Split key and value
    size_t key_len = equals - line;
    strncpy(key, line, key_len);
    key[key_len] = '\0';
    
    strcpy(value, equals + 1);
    
    // Trim whitespace
    trim_whitespace(key);
    trim_whitespace(value);
    
    return 1;
}

AppConfig* load_config(const char* filename) {
    AppConfig* config = (AppConfig*)malloc(sizeof(AppConfig));
    if (config == NULL) {
        printf("Failed to allocate memory for config!\n");
        return NULL;
    }
    
    // Set default values
    config->window_width = 800;
    config->window_height = 600;
    config->scroll_speed = 2;
    config->spacing = 200;
    config->text_color.r = 255;
    config->text_color.g = 255;
    config->text_color.b = 255;
    config->text_color.a = 255;
    strcpy(config->font_path, "fonts/arial.ttf");
    config->font_size = 24;
    config->sentence_count = 0;
    
    if (parse_config_file(filename, config) != 0) {
        printf("Failed to parse config file, using defaults\n");
    }
    
    return config;
}

void free_config(AppConfig* config) {
    if (config != NULL) {
        free(config);
    }
}

int parse_config_file(const char* filename, AppConfig* config) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Config file '%s' not found, using defaults\n", filename);
        return -1;
    }
    
    char line[512];
    char key[256];
    char value[256];
    
    while (fgets(line, sizeof(line), file)) {
        if (parse_ini_line(line, key, value)) {
            // Parse window settings
            if (strcmp(key, "window_width") == 0) {
                config->window_width = atoi(value);
            }
            else if (strcmp(key, "window_height") == 0) {
                config->window_height = atoi(value);
            }
            // Parse scroll settings
            else if (strcmp(key, "scroll_speed") == 0) {
                config->scroll_speed = atoi(value);
            }
            else if (strcmp(key, "spacing") == 0) {
                config->spacing = atoi(value);
            }
            // Parse text color
            else if (strcmp(key, "text_color_r") == 0) {
                config->text_color.r = atoi(value);
            }
            else if (strcmp(key, "text_color_g") == 0) {
                config->text_color.g = atoi(value);
            }
            else if (strcmp(key, "text_color_b") == 0) {
                config->text_color.b = atoi(value);
            }
            else if (strcmp(key, "text_color_a") == 0) {
                config->text_color.a = atoi(value);
            }
            // Parse font settings
            else if (strcmp(key, "font_path") == 0) {
                strncpy(config->font_path, value, sizeof(config->font_path) - 1);
                config->font_path[sizeof(config->font_path) - 1] = '\0';
            }
            else if (strcmp(key, "font_size") == 0) {
                config->font_size = atoi(value);
            }
            // Parse sentences
            else if (strncmp(key, "sentence_", 9) == 0) {
                int index = atoi(key + 9) - 1; // Convert sentence_1 to index 0
                if (index >= 0 && index < MAX_SENTENCES) {
                    strncpy(config->sentences[index], value, MAX_SENTENCE_LENGTH - 1);
                    config->sentences[index][MAX_SENTENCE_LENGTH - 1] = '\0';
                    if (index >= config->sentence_count) {
                        config->sentence_count = index + 1;
                    }
                }
            }
        }
    }
    
    fclose(file);
    return 0;
}