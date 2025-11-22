#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"
#include "fct_types.h"
#define taille_max 19

int main() {
    int width = 1000, height = 1000;
 
    MLV_create_window("Snake Menu", "Snake", width, height);
    MLV_Font* font_title = MLV_load_font("arial.ttf", 50);
    
    boucle_menu(width, height, font_title);
    
    MLV_free_window();
    return 0;
}
