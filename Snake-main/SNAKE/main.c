#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"
#include "fct_types.h"
#define taille_max 19

int main() {
    int width = 800, height = 600;
    int mx, my;
    int rx = width - 160; 
    int ry = height - 80; 
    int rw = 140;         
    int rh = 50;
    int bx;
    int bw;
    int bh;
    
    MLV_create_window("Snake Menu", "Snake", width, height);
    MLV_Font* font_title = MLV_load_font("arial.ttf", 50);
    
    afficher_menu(width, height, font_title);
    while (1) {

        MLV_wait_mouse(&mx, &my);

        bx = width/2 - 150;
        bw = 300;
        bh = 70;

        if (clic_bouton(bx, 200, bw, bh, mx, my)){
	  animation_clic_bouton(bx, 200, bw, bh, "Continuer Partie");
	  effacer_page();
	  afficher_continuer(width,height, font_title);
	}
        if (clic_bouton(bx, 300, bw, bh, mx, my)){
	  animation_clic_bouton(bx, 300, bw, bh, "Nouvelle Partie");
          main_jeu(height,width);
	  effacer_page();
	  afficher_nouvelle(width,height, font_title);
	}
        if (clic_bouton(bx, 400, bw, bh, mx, my)){
	  animation_clic_bouton(bx, 400, bw, bh, "2 Joueurs");
	  effacer_page();
	  afficher_2joueurs(width,height, font_title);
	}
	if (clic_bouton(rx, ry, rw, rh, mx, my)) {
	  animation_clic_bouton(rx, ry, rw, rh, "Retour");
	  effacer_page();
	  afficher_menu(width, height, font_title);
	}
    }
    MLV_free_window();
    return 0;
}
