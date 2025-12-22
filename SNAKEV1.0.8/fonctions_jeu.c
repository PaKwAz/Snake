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
    if ( (x+y) % 2 == 0 ) return MLV_COLOR_PERU;
    else return MLV_COLOR_SANDY_BROWN;
}

void afficher_image(MLV_Image* image, int x, int y, int hauteur){
    if (!image){
        printf("Erreur : Impossible de charger une ou plusieurs images.\n");
        exit(EXIT_FAILURE);
    }
    int taille_case = hauteur / taille_max;
    MLV_draw_image(image, x*taille_case, y*taille_case);
}


void affichage_train(cases plateau[taille_max][taille_max], int hauteur, int decalage){
    int decx, decy;
    int i,j;
    int bonne_case;
    int prochainx,prochainy;
    MLV_Color couleur;
    MLV_Image* image;
    MLV_Image* wagon = MLV_load_image("assets/wagon.png");
    MLV_Image* wagon_c = MLV_load_image("assets/wagon_cote.png");
    MLV_Image* loc_h = MLV_load_image("assets/locomotive_h.png");
    MLV_Image* loc_d = MLV_load_image("assets/locomotive_d.png");
    MLV_Image* loc_b = MLV_load_image("assets/locomotive_b.png");
    MLV_Image* loc_g = MLV_load_image("assets/locomotive_g.png");
    int taille_case = hauteur / taille_max;
    

    if (!wagon || !wagon_c || !loc_h || !loc_d || !loc_b || !loc_g) {
        printf("Erreur : Impossible de charger une ou plusieurs images.\n");
        exit(EXIT_FAILURE);
    }

    for ( i = 0 ; i < taille_max ; i ++ ){
        for ( j = 0 ; j < taille_max ; j ++){
            decx = 0, decy = 0;
            if (plateau[i][j].compteur >= 1) {
                if (plateau[i][j].serpent == 1) bonne_case = 1;
                
                switch(plateau[i][j].direction){
                    case 1: image = loc_h; decy -= decalage ; if (bonne_case)prochainx = i, prochainy = j-1 ; break;
                    case 2: image = loc_d; decx += decalage ; if (bonne_case)prochainx = i+1, prochainy = j ; break;
                    case 3: image = loc_b; decy += decalage ; if (bonne_case)prochainx = i, prochainy = i+1 ; break;
                    default: image = loc_g;decx -= decalage ; if (bonne_case)prochainx = i-1, prochainy = j ; break;
                    
                }
                if (plateau[i][j].direction % 2 == 0 && plateau[i][j].serpent == 0 ) image = wagon_c;
                else if ( plateau[i][j].serpent == 0 ) image = wagon;
                couleur = get_couleur_case(i,j);
                affichage_jeu(i,j,hauteur,couleur,1);
                MLV_draw_image(image, (i * taille_case + decx)%hauteur, (j * taille_case + decy )% hauteur);
                bonne_case = 0;
            }
            
        }

    }
    MLV_actualise_window();
    couleur = get_couleur_case(prochainx,prochainy);
    affichage_jeu(prochainx,prochainy,hauteur,couleur,1);
}




void affichage_jeu(int x, int y, int hauteur, MLV_Color couleur, int transformer_x_y){
    int taille_case = hauteur / taille_max;

    if (transformer_x_y == 1) {
        MLV_draw_filled_rectangle(x * taille_case, y * taille_case, taille_case, taille_case, couleur);
    } else {
        MLV_draw_filled_rectangle(x, y, taille_case, taille_case, couleur);
    }
}

void spawn_pomme(cases plateau[taille_max][taille_max], int hauteur){
    int xpomme, ypomme;
    MLV_Image* image = MLV_load_image("assets/charbon.png");
    do{
        xpomme = rand() % taille_max;
        ypomme = rand() % taille_max;
    } while (plateau[xpomme][ypomme].compteur != 0);
    
    plateau[xpomme][ypomme].compteur = -1;
    afficher_image(image, xpomme, ypomme, hauteur);
}

void init_plat(cases plateau[taille_max][taille_max], int *xtete, int *ytete, int hauteur){
    int i, j;
    for (i = 0; i < taille_max; i++){
        for (j = 0; j < taille_max; j++){
            plateau[i][j].serpent = 0;
            plateau[i][j].compteur = 0;
            plateau[i][j].direction = 0;
        }
    }
    *xtete = 9;
    *ytete = 9;
    plateau[9][9].serpent = 1;
    plateau[9][9].compteur = 1;
    plateau[9][9].direction = 1;
}

void affichage_initial(cases plateau[taille_max][taille_max], int hauteur, int largeur){
    int i, j;
    MLV_clear_window(MLV_COLOR_BLACK);
    for (i = 0; i < taille_max; i++){
        for (j = 0; j < taille_max; j++){
            if ((i + j) % 2 == 0) affichage_jeu(i, j, hauteur, MLV_COLOR_PERU, 1);
            else affichage_jeu(i, j, hauteur, MLV_COLOR_SANDY_BROWN, 1);
        }
    }
    spawn_pomme(plateau, hauteur);
    affichage_train(plateau,hauteur, 0);
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
                plateau[i][j].serpent = 0;
            }
        }
    }
}

void avancer_tete(cases plateau[taille_max][taille_max], int xtete, int ytete, int longueur, int direction){
    plateau[xtete][ytete].serpent = 1;
    plateau[xtete][ytete].compteur = longueur;
    plateau[xtete][ytete].direction = direction;
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

void attendre_et_ecouter(cases plateau[taille_max][taille_max], int hauteur, int attente, int direction_actuelle) {
    int debut_attente = MLV_get_time();
    int taille_case = hauteur / taille_max;
    int decalage = 0, compteur = 0;
    
    

    MLV_Event event;
    MLV_Keyboard_button touche;
    MLV_Button_state etat;

    while (MLV_get_time() - debut_attente < attente) {
        
        if ( compteur % 25 == 0 ){
            decalage += taille_case / 6;
            affichage_train(plateau, hauteur, decalage);

        }
        


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
        compteur += 5;
        MLV_wait_milliseconds(5);
    }
}


void main_jeu(int hauteur, int largeur){
    int pafini, direction, xtete, ytete, longueur, xenlever, yenlever, decr, score, meilleurscore1, meilleurscore2, meilleurscore3, attente;
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
    pafini = 1;
    affichage_initial(plateau, hauteur, largeur);
    afficher_menu_cote(&score);
    
    if (get_scores(&meilleurscore1, &meilleurscore2, &meilleurscore3)){
        printf("Erreur records.\n");
        meilleurscore1 = 0; meilleurscore2 = 0; meilleurscore3 = 0;
    }
    
    do {
        actualiser_direction_depuis_buffer(&direction);
        

        if (!pas_perdu(plateau, direction, &xtete, &ytete, &longueur, &decr, hauteur, &score)) {
            pafini = 0; 
        }

        attendre_et_ecouter(plateau, hauteur, attente, direction);

        avancer_tete(plateau, xtete, ytete, longueur, direction);

        if (decr == 1) {
            decrementer(plateau, xtete, ytete, &xenlever, &yenlever);
            
            if ((xenlever + yenlever) % 2 == 0) 
                couleur_fond = MLV_COLOR_PERU;
            else 
                couleur_fond = MLV_COLOR_SANDY_BROWN;

            affichage_jeu(xenlever, yenlever, hauteur, couleur_fond, 1);
        }
        
        decr = 1;
        
        affichage_train(plateau, hauteur, 0);
    } while (pafini);

    if (score > meilleurscore1) meilleurscore1 = score;
    else if ( score > meilleurscore2 ) meilleurscore2 = score;
    else if (score > meilleurscore3 ) meilleurscore3 = score;
    printf("%d, %d, %d",meilleurscore1, meilleurscore2, meilleurscore3);
    ecrire_res(meilleurscore1, meilleurscore2, meilleurscore3);
}