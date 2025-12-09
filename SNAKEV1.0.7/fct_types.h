#ifndef _FCT_TYPES_H_
#define _FCT_TYPES_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#define taille_max 19

typedef struct{
    int serpent;
    int compteur;
} cases;

void affichage_jeu(int x, int y, int hauteur, MLV_Color couleur, int transformer_x_y);

void spawn_pomme(cases plateau[taille_max][taille_max], int hauteur);

void init_plat(cases plateau[taille_max][taille_max], int *xtete, int *ytete, int hauteur);

void affichage_initial(cases plateau[taille_max][taille_max], int hauteur, int largeur);

int pas_perdu(cases plateau[taille_max][taille_max], int direction, int *xtete, int *ytete, int *longueur, int *decr, int hauteur, int *score);

void decrementer(cases plateau[taille_max][taille_max], int xtete, int ytete, int *xenlever, int *yenlever);

void avancer_tete(cases plateau[taille_max][taille_max], int xtete, int ytete, int longueur);

int get_scores( int *meilleurscore1, int *meilleurscore2, int *meilleurscore3);

void ecrire_res( int meilleurscore1, int meilleurscore2, int meilleurscore3);

void ajouter_au_buffer(int nouvelle_dir, int direction_actuelle);

void actualiser_direction_depuis_buffer(int *direction);

void attendre_et_ecouter(int anc_xtete, int anc_ytete, int nouv_xtete, int nouv_ytete, cases plateau[taille_max][taille_max], int hauteur, int attente, int decr, int direction_actuelle);

void main_jeu(int hauteur, int largeur);

#endif