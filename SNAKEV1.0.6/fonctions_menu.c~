#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"
#include "fct_types.h"

void animation_clic_bouton(MLV_Image* anim) {
    MLV_clear_window(MLV_COLOR_BLACK);
    
    MLV_draw_image(anim, 0, 0);
    MLV_actualise_window();
    
    MLV_wait_milliseconds(75);
}

int clic_bouton(int bx, int by, int bw, int bh, int mx, int my) {
    return (mx >= bx && mx <= bx + bw &&
            my >= by && my <= by + bh);
}

void afficher_menu(int width, int height) {
  MLV_Image* fond = MLV_load_image("assets/menu.jpg");
  MLV_clear_window(MLV_COLOR_BLACK);
  
  MLV_draw_image(fond, 0, 0);
  MLV_actualise_window();
}


void afficher_menu_cote(int *score) {

    MLV_Font* font = MLV_load_font( "assets/ARCADE_N.TTF", 50 );
    char score1[5];
    MLV_Image* fond = MLV_load_image("assets/cote.jpg");
    MLV_draw_image(fond, 1000, 0);
    sprintf(score1, "%d", *score);
    MLV_draw_text_with_font( 1150, 275, score1, font, MLV_COLOR_BLACK );
}

void afficher_continuer(int width, int height) {
  MLV_Image* fond = MLV_load_image("assets/importer.jpg");
  MLV_clear_window(MLV_COLOR_BLACK);
  
  MLV_draw_image(fond, 0, 0);
  MLV_actualise_window();
}

void afficher_nouvelle(int width, int height) {
  MLV_Image* fond = MLV_load_image("assets/ecraser.jpg");
  MLV_clear_window(MLV_COLOR_BLACK);
  
  MLV_draw_image(fond, 0, 0);
  MLV_actualise_window();
}

void afficher_2joueurs(int width, int height) {
  MLV_clear_window(MLV_rgba(30, 30, 30, 255));

  MLV_actualise_window();
}

void boucle_menu(int width, int height){
  int i = 1;
  int mx, my;
  MLV_Image* continuer = MLV_load_image("assets/menu_continuer.jpg");
  MLV_Image* nouvelle = MLV_load_image("assets/menu_nouvelle.jpg");
  MLV_Image* quitter = MLV_load_image("assets/menu_quitter.jpg");
  MLV_Image* joueurs = MLV_load_image("assets/menu_2joueurs.jpg");
  while (i==1) {

    afficher_menu(width, height);
    
    MLV_wait_mouse(&mx, &my);

    if (clic_bouton(76, 734, 361, 100, mx, my)){
      animation_clic_bouton(continuer);
      boucle_continuer(width,height);
    }
    if (clic_bouton(525, 734, 361, 100, mx, my)){
      animation_clic_bouton(joueurs);
      boucle_2joueurs(width,height);
    }
    if (clic_bouton(156, 466, 650, 180, mx, my)){
      animation_clic_bouton(nouvelle);
      boucle_nouvelle(width,height);
    }
    if (clic_bouton(1125, 658, 250, 242, mx, my)) {
      animation_clic_bouton(quitter);
      i=0;
    }
  }
}

void boucle_continuer(int width, int height){
  int i = 1;
  int mx,my;
  MLV_Image* un = MLV_load_image("assets/importer1.jpg");
  MLV_Image* deux = MLV_load_image("assets/importer2.jpg");
  MLV_Image* trois = MLV_load_image("assets/importer3.jpg");
  MLV_Image* retour = MLV_load_image("assets/importer_retour.jpg");
  
  while (i==1){

    afficher_continuer(width,height);
    
    MLV_wait_mouse(&mx,&my);

    if (clic_bouton(1131, 679, 203, 209, mx, my)) {
      animation_clic_bouton(retour);
      i=0;
    }
    if (clic_bouton(258, 398, 449, 124, mx, my)) {
      animation_clic_bouton(un);
    }
    if (clic_bouton(258, 557, 449, 124, mx, my)) {
      animation_clic_bouton(deux);
    }
    if (clic_bouton(258, 717, 449, 124, mx, my)) {
      animation_clic_bouton(trois);
    }
  }
}

void boucle_nouvelle(int width, int height){
  int i = 1;
  int mx,my;
  MLV_Image* un = MLV_load_image("assets/ecraser1.jpg");
  MLV_Image* deux = MLV_load_image("assets/ecraser2.jpg");
  MLV_Image* trois = MLV_load_image("assets/ecraser3.jpg");
  MLV_Image* retour = MLV_load_image("assets/ecraser_retour.jpg");
  
  while (i==1){

    afficher_nouvelle(width,height);
    
    MLV_wait_mouse(&mx,&my);

    if (clic_bouton(1131, 679, 203, 209, mx, my)) {
      animation_clic_bouton(retour);
      i=0;
    }
    if (clic_bouton(258, 398, 449, 124, mx, my)) {
      animation_clic_bouton(un);
    }
    if (clic_bouton(258, 557, 449, 124, mx, my)) {
      animation_clic_bouton(deux);
    }
    if (clic_bouton(258, 717, 449, 124, mx, my)) {
      animation_clic_bouton(trois);
    }
  }
}

void boucle_2joueurs(int width, int height){
  int i = 1;
  while (i==1){

    afficher_2joueurs(width,height);
    main_jeu(1000,1500);
  }
}

