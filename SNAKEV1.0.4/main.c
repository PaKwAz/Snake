#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"
#include "fct_types.h"
#define taille_max 19

int main() {
    int width = 1500, height = 1000;
 
    MLV_create_window("Snake Menu", "Snake", width, height);
    
    boucle_menu(width, height);
    
    MLV_free_window();
    return 0;
}
