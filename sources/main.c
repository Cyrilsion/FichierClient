#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "accueil.h"
#include "ajouter_client.h"
#include "coiffure.h"
#include "data.h"


int main( int argc, char* args[] )
{

    liste li;
    li = NULL;
    li = initialisation(li);

    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    TTF_Font *police_barre_recherche = NULL;
    police_barre_recherche = TTF_OpenFont("data/Candara.ttf", 40);
    TTF_Font *police_resultat_recherche = NULL;
    police_resultat_recherche = TTF_OpenFont("data/Candara.ttf", 20);

    ecran = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Fichier client", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 219, 219, 219));

    //////////initialisation de toutes les surfaces//////////////////

    SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL];
    initialisation_surfaces_accueil(ecran, surfaces_accueil, police_barre_recherche);
    SDL_Surface * surfaces_ajouter[NOMBRE_SURFACES_AJOUTER];
    initialisation_surfaces_ajouter(ecran, surfaces_ajouter, police_barre_recherche);
    SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE];
    initialisation_surfaces_coiffure(ecran, surfaces_coiffure, police_barre_recherche);

    ////////////////////////////////////////////////////////////////
    afficher_accueil(ecran, surfaces_accueil);
    li = attendre_evenement_accueil(ecran, li, surfaces_accueil, surfaces_ajouter, surfaces_coiffure, police_barre_recherche, police_resultat_recherche);
    enregistrer(li);

    TTF_Quit();
    SDL_Quit();


    return EXIT_SUCCESS;
}





