#ifndef ACCUEIL_H_INCLUDED
#define ACCUEIL_H_INCLUDED
#include "data.h"

liste attendre_evenement_accueil(SDL_Surface *ecran, liste li, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], SDL_Surface * surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], TTF_Font *police_barre_recherche, TTF_Font *police_resultat_recherche);
void afficher_accueil(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL]);
void initialisation_surfaces_accueil(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], TTF_Font *police_barre_recherche);
void afficher_historique(SDL_Surface * ecran, liste recherche[], int clientSelect, TTF_Font * police);
SDL_Surface * modifier_texte_recherche(SDL_Surface * ecran, SDL_Surface * barre_clean, SDL_Surface * texte_recherche, char * texte, TTF_Font *police);
void modifier_resultat_recherche(SDL_Surface * ecran, liste client[], SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], TTF_Font *police);
void blitTexteRecherche(SDL_Surface * ecran, SDL_Rect position,SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], liste client, TTF_Font *police);
void effacer_selection(SDL_Surface * ecran, int clientSelect, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], liste client[], TTF_Font * police);
void afficher_selection(int clientSelect, SDL_Surface * ecran, SDL_Surface * selection);
void blit_zoom(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], int zoom);

#endif // ACCUEIL_H_INCLUDED
