#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#ifndef FCT_MENU_H
#define FCT_MENU_H

void animation_clic_bouton(int x, int y, int w, int h, const char* texte);

void dessiner_bouton(int x, int y, int w, int h, const char* texte);

int clic_bouton(int bx, int by, int bw, int bh, int mx, int my);

void effacer_page();

void afficher_menu(int width, int height, MLV_Font* font_title);

void dessiner_bouton_retour(int width, int height);

void afficher_continuer(int width, int height, MLV_Font* font_title);

void afficher_nouvelle(int width, int height, MLV_Font* font_title);

void afficher_2joueurs(int width, int height, MLV_Font* font_title);

#endif
