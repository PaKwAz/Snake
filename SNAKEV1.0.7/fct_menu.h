#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#ifndef FCT_MENU_H
#define FCT_MENU_H

void animation_clic_bouton(MLV_Image* anim);

int clic_bouton(int bx, int by, int bw, int bh, int mx, int my);

void afficher_menu(MLV_Image* fond);

void afficher_menu_cote(int *score);

void afficher_continuer(MLV_Image* fond);

void afficher_nouvelle(MLV_Image* fond);

void afficher_2joueurs();

int boucle_menu(int width, int height);

int boucle_continuer(int width, int height);

int boucle_nouvelle(int width, int height);

void boucle_2joueurs(int width, int height);

#endif
