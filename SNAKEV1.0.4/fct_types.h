#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#define taille_max 19

typedef struct{
    int serpent;
    int compteur;
} cases;

#ifndef _FCT_TYPES_H_
#define _FCT_TYPES_H_

void spawn_pomme(cases plateau[taille_max][taille_max], int hauteur);

void init_plat(cases plateau[taille_max][taille_max], int *xtete, int *ytete, int hauteur);


void affichage_jeu(int x, int y, int hauteur, MLV_Color couleur); 


void affichage_initial(cases plateau[taille_max][taille_max], int hauteur, int largeur);

int pas_perdu(cases plateau[taille_max][taille_max], int direction, int *xtete, int *ytete, int *longueur, int *decr, int hauteur, int *score);

void decrementer(cases plateau[taille_max][taille_max], int xtete, int ytete, int *xenlever, int *yenlever);

void avancer_tete(cases plateau[taille_max][taille_max], int xtete, int ytete, int longueur);

void evenement(int *direction);

int get_scores( int *meilleurscore1, int *meilleurscore2, int *meilleurscore3);

void ecrire_res( int meilleurscore1, int meilleurscore2, int meilleurscore3);

void main_jeu(int hauteur, int largeur);

#endif