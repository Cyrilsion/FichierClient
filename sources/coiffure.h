#ifndef COIFFURE_H_INCLUDED
#define COIFFURE_H_INCLUDED
#include "data.h"

SDL_Surface * modifier_champ_ajouter(SDL_Surface * ecran, SDL_Surface * champAmodifier, SDL_Surface * blanc, char * texte, int champ_saisie, TTF_Font * police);
void initialisation_surfaces_coiffure(SDL_Surface * ecran, SDL_Surface *surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], TTF_Font * police);
void afficher_coiffure(SDL_Surface *ecran, SDL_Surface *surfaces_coiffure[NOMBRE_SURFACES_COIFFURE]);
void modifier_commentaire(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], char saisie[50], TTF_Font * police);
void effacer_selection_coiffure(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], int selection_type);
void afficher_selection_coiffure(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], int selection_type);


#endif // COIFFURE_H_INCLUDED
