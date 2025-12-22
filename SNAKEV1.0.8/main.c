#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"
#include "fct_types.h"
#define taille_max 19

int main() {
    int width = 1500, height = 1000;
 
    MLV_create_window("Snake Menu", "Snake", width, height);
    
    if (boucle_menu(width, height) == -1){
      printf("Une des images n'a pas pu être trouvée.\n");
      MLV_free_window();
      exit(EXIT_FAILURE);
    }
    
    MLV_free_window();
    exit(EXIT_SUCCESS);
}
