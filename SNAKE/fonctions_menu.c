#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "fct_menu.h"

void animation_clic_bouton(int x, int y, int w, int h, const char* texte) {
    int tw, th;
    MLV_get_size_of_text(texte, &tw, &th);

    // Dessiner le bouton "pressé"
    MLV_draw_filled_rectangle(x, y, w, h, MLV_rgba(100, 100, 100, 255)); // couleur plus claire
    MLV_draw_text(x + w/2 - tw/2, y + h/2 - th/2, texte, MLV_COLOR_WHITE);

    MLV_actualise_window();
    MLV_wait_milliseconds(75);  // petite pause pour l'animation

    // Remettre le bouton à l'état normal
    MLV_draw_filled_rectangle(x, y, w, h, MLV_rgba(50, 50, 50, 255));
    MLV_draw_text(x + w/2 - tw/2, y + h/2 - th/2, texte, MLV_COLOR_WHITE);
    MLV_actualise_window();
}

void dessiner_bouton(int x, int y, int w, int h, const char* texte) {
    int tw, th;

    /* Récupère la taille du texte */
    MLV_get_size_of_text(texte, &tw, &th);

    /* Dessiner le rectangle du bouton */
    MLV_draw_filled_rectangle(x, y, w, h, MLV_rgba(50, 50, 50, 255));

    /* Centrer le texte dans le bouton */
    MLV_draw_text(x + w/2 - tw/2, y + h/2 - th/2, texte, MLV_COLOR_WHITE);
}

int clic_bouton(int bx, int by, int bw, int bh, int mx, int my) {
    return (mx >= bx && mx <= bx + bw &&
            my >= by && my <= by + bh);
}

void effacer_page() {
    MLV_clear_window(MLV_rgba(30, 30, 30, 255));
    MLV_actualise_window();
}

void afficher_menu(int width, int height, MLV_Font* font_title) {
    int tw, th;

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(0, 0, width, height,
                              MLV_rgba(30, 30, 30, 255));

    /* Récupère la taille du texte AVEC la police */
    MLV_get_size_of_text_with_font("SNAKE GAME", &tw, &th, font_title);

    /* Titre centré */
    MLV_draw_text_with_font(
        width/2 - tw/2,
        70,
        "SNAKE GAME",
        font_title,
        MLV_COLOR_GREEN
    );

    /* Boutons */
    int bx = width/2 - 150;
    int bw = 300;
    int bh = 70;

    dessiner_bouton(bx, 200, bw, bh, "Continuer Partie");
    dessiner_bouton(bx, 300, bw, bh, "Nouvelle Partie");
    dessiner_bouton(bx, 400, bw, bh, "2 Joueurs");

    MLV_actualise_window();
}

/* Fonction pour dessiner le bouton Retour */
void dessiner_bouton_retour(int width, int height) {
    dessiner_bouton(width - 160, height - 80, 140, 50, "Retour");
}

/* Fonction pour continuer la partie */
void afficher_continuer(int width, int height, MLV_Font* font_title) {
    int tw, th;
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(0, 0, width, height,MLV_rgba(30, 30, 30, 255));
    MLV_get_size_of_text_with_font("Continuer Partie", &tw, &th, font_title);
    MLV_draw_text_with_font(width/2 - tw/2,70,"Continuer Partie",font_title,MLV_COLOR_GREEN);
    dessiner_bouton_retour(width, height);
    MLV_actualise_window();
}

/* Fonction pour nouvelle partie */
void afficher_nouvelle(int width, int height, MLV_Font* font_title) {
    int tw, th;
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(0, 0, width, height,MLV_rgba(30, 30, 30, 255));
    MLV_get_size_of_text_with_font("Nouvelle Partie", &tw, &th, font_title);
    MLV_draw_text_with_font(width/2 - tw/2,70,"Nouvelle Partie",font_title,MLV_COLOR_GREEN);
    dessiner_bouton_retour(width, height);
    MLV_actualise_window();
}

/* Fonction pour mode 2 joueurs */
void afficher_2joueurs(int width, int height, MLV_Font* font_title) {
    int tw, th;
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(0, 0, width, height,MLV_rgba(30, 30, 30, 255));
    MLV_get_size_of_text_with_font("Jouer à 2 joueurs", &tw, &th, font_title);
    MLV_draw_text_with_font(width/2 - tw/2,70,"Jouer à 2 joueurs",font_title,MLV_COLOR_GREEN);
    dessiner_bouton_retour(width, height);
    MLV_actualise_window();
}



