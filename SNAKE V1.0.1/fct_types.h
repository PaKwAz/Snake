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
void spawn_pomme(cases plateau[taille_max][taille_max]);

void init_plat(cases plateau[taille_max][taille_max],int *xtete,int *ytete);

void affichage(cases plateau[taille_max][taille_max],int hauteur, int largeur);

int pas_perdu(cases plateau[taille_max][taille_max],int direction,int *xtete, int *ytete,int *longueur);

void decrementer(cases plateau[taille_max][taille_max],int xtete,int ytete);

void avancer_tete(cases plateau[taille_max][taille_max],int xtete,int ytete,int longueur);

void evenement(int *direction);

void main_jeu(int hauteur, int largeur);

#endif