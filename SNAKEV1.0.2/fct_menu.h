#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#ifndef FCT_MENU_H
#define FCT_MENU_H

void animation_clic_bouton(int x, int y, int w, int h, const char* texte);

void dessiner_bouton(int x, int y, int w, int h, const char* texte);

int clic_bouton(int bx, int by, int bw, int bh, int mx, int my);

void afficher_menu(int width, int height, MLV_Font* font_title);

void dessiner_bouton_retour(int width, int height);

void dessiner_bouton_quitter(int width, int height);

void dessiner_boutons_impexp(int width, int height);

void afficher_charger(int width, int height, MLV_Font* font_title);

void afficher_nouvelle(int width, int height, MLV_Font* font_title);

void afficher_2joueurs(int width, int height, MLV_Font* font_title);

void boucle_menu(int width, int height, MLV_Font* font_title);

void boucle_charger(int width, int height, MLV_Font* font_title);

void boucle_nouvelle(int width, int height, MLV_Font* font_title);

void boucle_2joueurs(int width, int height, MLV_Font* font_title);

#endif
