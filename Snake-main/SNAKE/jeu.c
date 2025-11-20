#include "types.h"
#define taille_max 19


void spawn_pomme(cases plateau[taille_max][taille_max]){
    int xpomme,ypomme;
    do{
        xpomme = rand()%19;
        ypomme = rand()%19;
    } while (plateau[xpomme][ypomme].compteur != 0);
    plateau[xpomme][ypomme].compteur = -1;
    printf("%d,%d",xpomme,ypomme);
}

void init_plat(cases plateau[taille_max][taille_max],int *xtete,int *ytete){
    int i,j;
    for (i = 0 ; i < taille_max ; i++){
        for (j = 0 ; j < taille_max ; j++){
            plateau[i][j].serpent = 0;
            plateau[i][j].compteur = 0;
        }
    }
    plateau[9][9].serpent = 1;
    plateau[9][9].compteur = 1;
    *xtete = 9;
    *ytete = 9;
    spawn_pomme(plateau);
}

void affichage(cases plateau[taille_max][taille_max],int hauteur, int largeur){
    int compteur1, compteur2,i,j,etat;
    MLV_clear_window(MLV_COLOR_BLACK);
    compteur1 = 0, compteur2 = 0;
    etat = 0;
    for (  i = 0 ; i < taille_max ; i++){
        for (j = 0 ; j < taille_max ; j++){
            switch(plateau[i][j].compteur){
            case 0:
                if (etat == 0){
                    MLV_draw_filled_rectangle(compteur1, compteur2, hauteur/taille_max, largeur/taille_max, MLV_COLOR_DARK_GREEN );
                    etat = 1;
                }
                else{
                    MLV_draw_filled_rectangle(compteur1, compteur2, hauteur/taille_max, largeur/taille_max, MLV_COLOR_YELLOW_GREEN );
                    etat = 0;
                    
                }
                break;
            case (-1):
                MLV_draw_filled_rectangle(compteur1, compteur2, hauteur/taille_max, largeur/taille_max, MLV_COLOR_RED );
                etat = (etat + 1)%2;
                break;
            default:
                MLV_draw_filled_rectangle(compteur1, compteur2, hauteur/taille_max, largeur/taille_max, MLV_COLOR_WHITE );
                etat = (etat + 1)%2;
                
            }
            compteur1 += largeur/taille_max;
        }
        compteur1 = 0;
        compteur2 += hauteur/taille_max;
    }
    MLV_actualise_window();
    MLV_wait_milliseconds(150);
}

int pas_perdu(cases plateau[taille_max][taille_max],int direction,int *xtete, int *ytete,int *longueur){
    int nouv_x,nouv_y,resultat;
    switch(direction){
    case 1:
        nouv_x=*xtete;
        nouv_y=*ytete-1;
        if (nouv_y < 0) nouv_y = taille_max-1;
        break;
    case 2:
        nouv_x=((*xtete+1)%taille_max);
        nouv_y=*ytete;
        break;
    case 3:
        nouv_x=*xtete;
        nouv_y=((*ytete+1)%taille_max);
        break;
    case 4:
        nouv_x=*xtete-1;
        nouv_y=*ytete;
        if (nouv_x < 0) nouv_x = taille_max-1;
        break;
    default : exit(EXIT_FAILURE);
    }
    switch(plateau[nouv_x][nouv_y].compteur){
    case 0:
        resultat=1;
        break;
    case (-1):
        resultat=1;
        *longueur = *longueur + 1;
        spawn_pomme(plateau);
        break;
    default:
        resultat = 0;
    }

    *xtete = nouv_x;
    *ytete = nouv_y;

    
    return resultat;
    
}

void decrementer(cases plateau[taille_max][taille_max],int xtete,int ytete){
    int i,j;
    for (i = 0; i < taille_max ; i ++){
        for ( j = 0 ; j < taille_max ; j ++ ){
            if (  plateau[i][j].compteur >= 1  && ( i != xtete || j != ytete)){
                plateau[i][j].compteur --;
                plateau[i][j].serpent = 0;
            }
        }
    }
}

void avancer_tete(cases plateau[taille_max][taille_max],int xtete,int ytete,int longueur){
    plateau[xtete][ytete].serpent = 1;
    plateau[xtete][ytete].compteur = longueur;
}

void evenement(int *direction){
    MLV_Keyboard_button touche;
    MLV_Button_state etat;
    MLV_Event event;
    event = MLV_get_event( 
        &touche, NULL, NULL, 
        NULL, NULL,
        NULL, NULL, NULL,
        &etat
        );
    if (event == MLV_KEY){
        if (etat == MLV_PRESSED ){
            switch(touche){
            case 'z':
                *direction = 4;
                break;
            case 'd':
                *direction = 3;
                break;
            case 's':
                *direction = 2;
                break;
            case 'q':
                *direction = 1;
                break;
            default: direction = direction;
            }
        }
    }
}



int main_jeu(int hauteur, int largeur){
    int direction,xtete,ytete,longueur;
    cases plateau[taille_max][taille_max];
    srand(time(NULL));
    longueur = 1;
    xtete = 9, ytete = 9;
    direction=1;
    hauteur = 1500;
    largeur = 1500;
    init_plat(plateau,&xtete,&ytete);
    affichage(plateau,hauteur,largeur);
    do {
        avancer_tete(plateau,xtete,ytete,longueur);
        decrementer(plateau,xtete,ytete); 
        affichage(plateau,hauteur,largeur);
        evenement(&direction);
        
    } while (pas_perdu(plateau,direction,&xtete,&ytete,&longueur));

    

    MLV_free_window();
    exit(EXIT_SUCCESS);
}