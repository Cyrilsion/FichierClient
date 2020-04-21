#ifndef AJOUTER_CLIENT_H_INCLUDED
#define AJOUTER_CLIENT_H_INCLUDED
#include "data.h"

liste attendre_evenement_ajouter(SDL_Surface * ecran, SDL_Surface * surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], liste li, TTF_Font * police_barre_recherche);
void initialisation_surfaces_ajouter(SDL_Surface *ecran, SDL_Surface *surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], TTF_Font * police);
void afficher_ajouter(SDL_Surface *ecran, SDL_Surface *surfaces_ajouter[NOMBRE_SURFACES_AJOUTER]);
void drawEmptyRect(SDL_Surface * surf,int posX, int posY, int width, int length, int R, int G, int B);
SDL_Surface * modifier_texte_client(SDL_Surface * ecran, SDL_Surface * texteClient, liste client, TTF_Font * police);
SDL_Surface * modifier_champ_ajouter(SDL_Surface * ecran, SDL_Surface * champAmodifier, SDL_Surface * blanc, char * texte, int champ_saisie, TTF_Font * police);


#endif // AJOUTER_CLIENT_H_INCLUDED
