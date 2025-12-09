#include "fct_types.h"
#include "fct_menu.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MLV/MLV_all.h>

int buffer_direction[3];
int taille_buffer = 0;

MLV_Color get_couleur_case(int x, int y){
    if ( (x+y) % 2 == 0 ) return MLV_COLOR_DARK_GREEN;
    else return MLV_COLOR_YELLOW_GREEN;
}

void dessiner_rect_securise(int x, int y, int w, int h, MLV_Color color, int limite_x) {
    if (x >= limite_x) return; 
    if (x + w > limite_x) w = limite_x - x;
    MLV_draw_filled_rectangle(x, y, w, h, color);
}

void affichage_jeu(int x, int y, int hauteur, MLV_Color couleur, int transformer_x_y){
    int taille_case = hauteur / taille_max;
    int limite_plateau = taille_max * taille_case; 

    if (transformer_x_y == 1) {
        dessiner_rect_securise(x * taille_case, y * taille_case, taille_case, taille_case, couleur, limite_plateau);
    } else {
        dessiner_rect_securise(x, y, taille_case, taille_case, couleur, limite_plateau);
    }
}

void spawn_pomme(cases plateau[taille_max][taille_max], int hauteur){
    int xpomme, ypomme;
    do{
        xpomme = rand() % taille_max;
        ypomme = rand() % taille_max;
    } while (plateau[xpomme][ypomme].compteur != 0);
    
    plateau[xpomme][ypomme].compteur = -1;
    affichage_jeu(xpomme, ypomme, hauteur, MLV_COLOR_RED, 1);
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
            if ((i + j) % 2 == 0) affichage_jeu(i, j, hauteur, MLV_COLOR_DARK_GREEN, 1);
            else affichage_jeu(i, j, hauteur, MLV_COLOR_YELLOW_GREEN, 1);

            if (plateau[i][j].compteur == -1) affichage_jeu(i, j, hauteur, MLV_COLOR_RED, 1);
            else if (plateau[i][j].compteur > 0) affichage_jeu(i, j, hauteur, MLV_COLOR_WHITE, 1);
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
    case 1: nouv_y = *ytete - 1; if (nouv_y < 0) nouv_y = taille_max - 1; break;
    case 2: nouv_x = (*xtete + 1) % taille_max; break;
    case 3: nouv_y = (*ytete + 1) % taille_max; break;
    case 4: nouv_x = *xtete - 1; if (nouv_x < 0) nouv_x = taille_max - 1; break;
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

int get_scores( int *meilleurscore1, int *meilleurscore2, int *meilleurscore3){
    int ret1 = 0, ret2 = 0, ret3 = 0, score1, score2, score3;
    FILE* records = fopen( "records.txt", "r" );
    if ( records == NULL ) {
        printf("Création records...\n");
    } else {
        if ( fscanf(records,"%d",&score1) != 1 ) ret1 = 1;
        if ( fscanf(records,"%d",&score2) != 1 ) ret2 = 1;
        if ( fscanf(records,"%d",&score3) != 1 ) ret3 = 1;
    }
    *meilleurscore1 = score1; *meilleurscore2 = score2; *meilleurscore3 = score3;
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

void ajouter_au_buffer(int nouvelle_dir, int direction_actuelle) {
    if (taille_buffer >= 3) return;
    int derniere_dir;
    if (taille_buffer > 0) derniere_dir = buffer_direction[taille_buffer - 1];
    else derniere_dir = direction_actuelle;

    if (derniere_dir == 1 && nouvelle_dir == 3) return;
    if (derniere_dir == 3 && nouvelle_dir == 1) return;
    if (derniere_dir == 2 && nouvelle_dir == 4) return;
    if (derniere_dir == 4 && nouvelle_dir == 2) return;
    if (derniere_dir == nouvelle_dir) return;

    buffer_direction[taille_buffer] = nouvelle_dir;
    taille_buffer++;
}

void actualiser_direction_depuis_buffer(int *direction) {
    if (taille_buffer > 0) {
        *direction = buffer_direction[0];
        for(int i = 0; i < taille_buffer - 1; i++){
            buffer_direction[i] = buffer_direction[i+1];
        }
        taille_buffer--;
    }
}

void attendre_et_ecouter(int anc_xtete, int anc_ytete, int nouv_xtete, int nouv_ytete, cases plateau[taille_max][taille_max], int hauteur, int attente, int decr, int direction_actuelle) {
    int debut_attente = MLV_get_time();
    int taille_case = hauteur / taille_max;
    int limite_x = taille_max * taille_case;
    
    int tete_depart_x = anc_xtete * taille_case;
    int tete_depart_y = anc_ytete * taille_case;
    int tete_cible_x = nouv_xtete * taille_case;
    int tete_cible_y = nouv_ytete * taille_case;
    int anim_tete = 1;
    if (abs(tete_cible_x - tete_depart_x) > taille_case || abs(tete_cible_y - tete_depart_y) > taille_case) anim_tete = 0;

    int queue_depart_x = 0, queue_depart_y = 0;
    int queue_cible_x = 0, queue_cible_y = 0;
    int anim_queue = 0;
    int est_taille_un = 0;

    if (decr == 1) {
        int tx_grille = -1, ty_grille = -1;
        for(int i=0; i<taille_max; i++) {
            for(int j=0; j<taille_max; j++) {
                if(plateau[i][j].compteur == 1) {
                    tx_grille = i;
                    ty_grille = j;
                }
            }
        }

        if (tx_grille != -1) {
            queue_depart_x = tx_grille * taille_case;
            queue_depart_y = ty_grille * taille_case;
            
            if (tx_grille == anc_xtete && ty_grille == anc_ytete) {
                est_taille_un = 1;
            }

            if (!est_taille_un) {
                int voisins[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
                for(int k=0; k<4; k++) {
                    int vx = (tx_grille + voisins[k][0] + taille_max) % taille_max;
                    int vy = (ty_grille + voisins[k][1] + taille_max) % taille_max;
                    
                    if(plateau[vx][vy].compteur == 2) {
                        queue_cible_x = vx * taille_case;
                        queue_cible_y = vy * taille_case;
                        anim_queue = 1;
                        if (abs(queue_cible_x - queue_depart_x) > taille_case || abs(queue_cible_y - queue_depart_y) > taille_case) anim_queue = 0;
                        break;
                    }
                }
            }
        }
    }

    MLV_Event event;
    MLV_Keyboard_button touche;
    MLV_Button_state etat;

    while (MLV_get_time() - debut_attente < attente) {
        float ratio = (float)(MLV_get_time() - debut_attente) / (float)attente;
        if (ratio > 1.0) ratio = 1.0;

        if (est_taille_un) {
            dessiner_rect_securise(tete_depart_x, tete_depart_y, taille_case, taille_case, get_couleur_case(anc_xtete, anc_ytete), limite_x);
        } else {
            dessiner_rect_securise(tete_depart_x, tete_depart_y, taille_case, taille_case, MLV_COLOR_WHITE, limite_x);
        }

        dessiner_rect_securise(tete_cible_x, tete_cible_y, taille_case, taille_case, get_couleur_case(nouv_xtete, nouv_ytete), limite_x);

        if (anim_tete) {
            int hx = tete_depart_x + (int)((tete_cible_x - tete_depart_x) * ratio);
            int hy = tete_depart_y + (int)((tete_cible_y - tete_depart_y) * ratio);
            dessiner_rect_securise(hx, hy, taille_case, taille_case, MLV_COLOR_WHITE, limite_x);
        } else {
            dessiner_rect_securise(tete_cible_x, tete_cible_y, taille_case, taille_case, MLV_COLOR_WHITE, limite_x);
        }

        if (anim_queue && decr == 1) {
            int tx_grille = queue_depart_x / taille_case;
            int ty_grille = queue_depart_y / taille_case;
            dessiner_rect_securise(queue_depart_x, queue_depart_y, taille_case, taille_case, get_couleur_case(tx_grille, ty_grille), limite_x);
            
            int tx = queue_depart_x + (int)((queue_cible_x - queue_depart_x) * ratio);
            int ty = queue_depart_y + (int)((queue_cible_y - queue_depart_y) * ratio);
            dessiner_rect_securise(tx, ty, taille_case, taille_case, MLV_COLOR_WHITE, limite_x);
        }

        MLV_actualise_window();

        event = MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat);
        if (event == MLV_KEY && etat == MLV_PRESSED) {
            int nouv = 0;
            switch(touche){
                case 'z': nouv = 1; break;
                case 'd': nouv = 2; break;
                case 's': nouv = 3; break;
                case 'q': nouv = 4; break;
                default: break;
            }
            if (nouv != 0) ajouter_au_buffer(nouv, direction_actuelle);
        }
        MLV_wait_milliseconds(5);
    }
}

void main_jeu(int hauteur, int largeur){
    int direction, xtete, ytete, longueur, xenlever, yenlever, decr, score, meilleurscore1, meilleurscore2, meilleurscore3, attente;
    cases plateau[taille_max][taille_max];
    MLV_Color couleur_fond;

    attente = 130;
    score = 0;
    srand(time(NULL));
    decr = 1;
    longueur = 1;
    init_plat(plateau, &xtete, &ytete, hauteur);
    xenlever = xtete;
    yenlever = ytete;
    direction = 1;
    taille_buffer = 0;

    affichage_initial(plateau, hauteur, largeur);
    afficher_menu_cote(&score);
    if (get_scores(&meilleurscore1, &meilleurscore2, &meilleurscore3)){
        printf("Erreur records.\n");
        meilleurscore1 = 0; meilleurscore2 = 0; meilleurscore3 = 0;
    }
    
    do {
        actualiser_direction_depuis_buffer(&direction);
        
        int anc_xtete = xtete;
        int anc_ytete = ytete;

        if (!pas_perdu(plateau, direction, &xtete, &ytete, &longueur, &decr, hauteur, &score)) {
            break; 
        }

        attendre_et_ecouter(anc_xtete, anc_ytete, xtete, ytete, plateau, hauteur, attente, decr, direction);

        avancer_tete(plateau, xtete, ytete, longueur);

        if (decr == 1) {
            decrementer(plateau, xtete, ytete, &xenlever, &yenlever);
            
            if ((xenlever + yenlever) % 2 == 0) 
                couleur_fond = MLV_COLOR_DARK_GREEN;
            else 
                couleur_fond = MLV_COLOR_YELLOW_GREEN;

            affichage_jeu(xenlever, yenlever, hauteur, couleur_fond, 1);
        }
        
        decr = 1;
        
    } while (1);

    if (score > meilleurscore1) meilleurscore1 = score;
    else if ( score > meilleurscore2 ) meilleurscore2 = score;
    else if (score > meilleurscore3 ) meilleurscore3 = score;
    printf("%d, %d, %d",meilleurscore1, meilleurscore2, meilleurscore3);
    ecrire_res(meilleurscore1, meilleurscore2, meilleurscore3);
}