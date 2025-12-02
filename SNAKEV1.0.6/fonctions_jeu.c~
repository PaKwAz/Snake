#include "fct_types.h"
#include "fct_menu.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>



void affichage_jeu(int x, int y, int hauteur, MLV_Color couleur){
    int taille_case = hauteur / taille_max;
    MLV_draw_filled_rectangle(x * taille_case, y * taille_case, taille_case, taille_case, couleur);
}

void spawn_pomme(cases plateau[taille_max][taille_max], int hauteur){
    int xpomme, ypomme;
    do{
        xpomme = rand() % taille_max;
        ypomme = rand() % taille_max;
    } while (plateau[xpomme][ypomme].compteur != 0);
    
    plateau[xpomme][ypomme].compteur = -1;
    affichage_jeu(xpomme, ypomme, hauteur, MLV_COLOR_RED);
}

void init_plat(cases plateau[taille_max][taille_max], int *xtete, int *ytete, int hauteur){
    int i, j;
    for (i = 0; i < taille_max; i++){
        for (j = 0; j < taille_max; j++){
            plateau[i][j].serpent = 0;
            plateau[i][j].compteur = 0;
        }
    }
    *xtete = 9;
    *ytete = 9;
    plateau[9][9].serpent = 1;
    plateau[9][9].compteur = 1;
    spawn_pomme(plateau, hauteur);
}

void affichage_initial(cases plateau[taille_max][taille_max], int hauteur, int largeur){
    int i, j;
    MLV_clear_window(MLV_COLOR_BLACK);
    for (i = 0; i < taille_max; i++){
        for (j = 0; j < taille_max; j++){
            if ((i + j) % 2 == 0)
                affichage_jeu(i, j, hauteur, MLV_COLOR_DARK_GREEN);
            else
                affichage_jeu(i, j, hauteur, MLV_COLOR_YELLOW_GREEN);

            if (plateau[i][j].compteur == -1)
                affichage_jeu(i, j, hauteur, MLV_COLOR_RED);
            else if (plateau[i][j].compteur > 0)
                affichage_jeu(i, j, hauteur, MLV_COLOR_WHITE);
        }
    }
    MLV_actualise_window();
    MLV_wait_milliseconds(150);
}

int pas_perdu(cases plateau[taille_max][taille_max], int direction, int *xtete, int *ytete, int *longueur, int *decr, int hauteur, int *score){
    int nouv_x = *xtete;
    int nouv_y = *ytete;
    int resultat = 1;

    switch(direction){
    case 1:
        nouv_y = *ytete - 1;
        if (nouv_y < 0) nouv_y = taille_max - 1;
        break;
    case 2:
        nouv_x = (*xtete + 1) % taille_max;
        break;
    case 3:
        nouv_y = (*ytete + 1) % taille_max;
        break;
    case 4:
        nouv_x = *xtete - 1;
        if (nouv_x < 0) nouv_x = taille_max - 1;
        break;
    default: exit(EXIT_FAILURE);
    }

    if (plateau[nouv_x][nouv_y].compteur > 0){
        resultat = 0;
    }
    else if (plateau[nouv_x][nouv_y].compteur == -1){
        resultat = 1;
        *longueur = *longueur + 1;
        spawn_pomme(plateau, hauteur);
        *decr = 0;
        *score += 1;
        afficher_menu_cote(score);
    }
    else {
        resultat = 1;
    }

    *xtete = nouv_x;
    *ytete = nouv_y;
    return resultat;
}

void decrementer(cases plateau[taille_max][taille_max], int xtete, int ytete, int *xenlever, int *yenlever){
    int i, j;
    for (i = 0; i < taille_max; i++){
        for (j = 0; j < taille_max; j++){
            if (plateau[i][j].compteur >= 1 && (i != xtete || j != ytete)){
                if (plateau[i][j].compteur == 1){
                    *xenlever = i;
                    *yenlever = j;
                }
                plateau[i][j].compteur--;
                if (plateau[i][j].compteur == 0) plateau[i][j].serpent = 0;
            }
        }
    }
}

void avancer_tete(cases plateau[taille_max][taille_max], int xtete, int ytete, int longueur){
    plateau[xtete][ytete].serpent = 1;
    plateau[xtete][ytete].compteur = longueur;
}

void evenement(int *direction){
    MLV_Keyboard_button touche;
    MLV_Button_state etat;
    MLV_Event event;
    event = MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat);
    if (event == MLV_KEY && etat == MLV_PRESSED){
        switch(touche){
        case 'z': if (*direction != 3) *direction = 1; break;
        case 'd': if (*direction != 4) *direction = 2; break;
        case 's': if (*direction != 1) *direction = 3; break;
        case 'q': if (*direction != 2) *direction = 4; break;
        default: break;
        }
    }
}

int get_scores( int *meilleurscore1, int *meilleurscore2, int *meilleurscore3){
    int ret1 = 0, ret2 = 0, ret3 = 0, score1, score2, score3;
    FILE* records = fopen( "records.txt", "r" );
    if ( records == NULL ) {
        if ( records == NULL ) {
            printf("erreur lors de la création du fichier");
            exit(EXIT_FAILURE);
        }
        
        
    }
    else {
        if ( fscanf(records,"%d",&score1) != 1 ) ret1 = 1;
        if ( fscanf(records,"%d",&score2) != 1 ) ret2 = 1;
        if ( fscanf(records,"%d",&score3) != 1 ) ret3 = 1;
    }
    *meilleurscore1 = score1;
    *meilleurscore2 = score2;
    *meilleurscore3 = score3;
    fclose(records);
    return (ret1 || ret2 || ret3);
}

void ecrire_res( int meilleurscore1, int meilleurscore2, int meilleurscore3){
    FILE* records = fopen( "records.txt", "w" );
    fprintf(records,"%d\n", meilleurscore1);
    fprintf(records,"%d\n", meilleurscore2);
    fprintf(records,"%d\n", meilleurscore3);
    fclose(records);
}

void main_jeu(int hauteur, int largeur){
    int direction, xtete, ytete, longueur, xenlever, yenlever, decr, score, meilleurscore1, meilleurscore2, meilleurscore3;
    cases plateau[taille_max][taille_max];
    MLV_Color couleur_fond;


    score = 0;
    srand(time(NULL));
    decr = 1;
    longueur = 1;
    init_plat(plateau, &xtete, &ytete, hauteur);
    xenlever = xtete;
    yenlever = ytete;
    direction = 1;
    affichage_initial(plateau, hauteur, largeur);
    afficher_menu_cote(&score);
    if (get_scores(&meilleurscore1, &meilleurscore2, &meilleurscore3)){
        printf("Erreur lors de la récupération des records, scores réinitialisés");
            meilleurscore1 = 0;
            meilleurscore2 = 0;
            meilleurscore3 = 0;
    }
    
    do {
        avancer_tete(plateau, xtete, ytete, longueur);
        
        affichage_jeu(xtete, ytete, hauteur, MLV_COLOR_WHITE);
	

        if(decr == 1) {
            decrementer(plateau, xtete, ytete, &xenlever, &yenlever);
            if ((xenlever + yenlever) % 2 == 0) 
                couleur_fond = MLV_COLOR_DARK_GREEN;
            else 
                couleur_fond = MLV_COLOR_YELLOW_GREEN;
            
            affichage_jeu(xenlever, yenlever, hauteur, couleur_fond);
        }
        
        MLV_actualise_window();
        MLV_wait_milliseconds(150);
        
        evenement(&direction);
        decr = 1;
        
    } while (pas_perdu(plateau, direction, &xtete, &ytete, &longueur, &decr, hauteur, &score));
    if (score > meilleurscore1) meilleurscore1 = score;
    else if ( score > meilleurscore2 ) meilleurscore2 = score;
    else if (score > meilleurscore3 ) meilleurscore3 = score;
    printf("%d, %d, %d",meilleurscore1, meilleurscore2, meilleurscore3);
    ecrire_res(meilleurscore1, meilleurscore2, meilleurscore3);
}
