#include "coiffure.h"


liste attendre_evenement_coiffure(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], liste client, TTF_Font * police_barre_recherche)    {

    int i, j = 0;
    int selection_type = 1;
    char saisie[30];
    saisie[0] = '\0';
    char caractere;
    SDL_Event event;

    afficher_selection_coiffure(ecran, surfaces_coiffure, selection_type);
    SDL_FreeSurface(surfaces_coiffure[TEXTECLIENT]);
    surfaces_coiffure[TEXTECLIENT] = modifier_texte_client(ecran, surfaces_coiffure[TEXTECLIENT], client, police_barre_recherche);

    while (1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            return NULL;
            break;

        case SDL_MOUSEBUTTONUP:
            if(event.button.x >= 1050 && event.button.x <= 1178 && event.button.y >= 550 && event.button.y <= 678)
            {
                    //valider
                    client = ajouter_historique(client, selection_type, saisie);
                    return client;

            }
            if(event.button.x >= 1150 && event.button.x <= 1214 && event.button.y >= 30 && event.button.y <= 94)
            {

                    //retour
                    return NULL;

            }
            for(i = 1; i <= 5; i++) {

                if(event.button.x >= 150 && event.button.x <= 650 && event.button.y >= i * 100 && event.button.y <= 50 + i * 100)    {

                    effacer_selection_coiffure(ecran, surfaces_coiffure, selection_type);
                    selection_type = i;
                    afficher_selection_coiffure(ecran, surfaces_coiffure, selection_type);

                }

            }

            break;
        case SDL_KEYDOWN:
            if((((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z ) || event.key.keysym.sym==SDLK_SEMICOLON  || event.key.keysym.sym == SDLK_SPACE || (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) || (event.key.keysym.sym >= SDLK_KP0 && event.key.keysym.sym <= SDLK_KP9)) && j <30) || event.key.keysym.sym==SDLK_BACKSPACE)   {
            caractere = caractere_saisi(event);
            if(caractere == '<') {
                    j = j - 2;
                    if(j < -1) j = -1;
            }
            else saisie[j] = caractere;
            saisie[j + 1] = '\0';
            SDL_FreeSurface(surfaces_coiffure[TEXTECOMMENTAIRE1]);
            SDL_FreeSurface(surfaces_coiffure[TEXTECOMMENTAIRE2]);
            modifier_commentaire(ecran, surfaces_coiffure, saisie, police_barre_recherche);
            j++;
            }
            if(event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_TAB)   {

                effacer_selection_coiffure(ecran, surfaces_coiffure, selection_type);
                selection_type++;
                if(selection_type > 5)  selection_type = 1;
                afficher_selection_coiffure(ecran, surfaces_coiffure, selection_type);

            }
            if(event.key.keysym.sym==SDLK_UP)   {

                effacer_selection_coiffure(ecran, surfaces_coiffure, selection_type);
                selection_type--;
                if(selection_type < 1)  selection_type = 5;
                afficher_selection_coiffure(ecran, surfaces_coiffure, selection_type);

            }
            if(event.key.keysym.sym==SDLK_ESCAPE)   {

                //retour
                return NULL;

            }
            if(event.key.keysym.sym==SDLK_RETURN)   {

                //valider
                client = ajouter_historique(client, selection_type, saisie);
                return client;

            }
        break;
        }
    }
}

void initialisation_surfaces_coiffure(SDL_Surface * ecran, SDL_Surface *surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], TTF_Font * police)    {

    surfaces_coiffure[TYPE] = NULL;
    surfaces_coiffure[TYPE] = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_coiffure[TYPE], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    surfaces_coiffure[SELECTION] = NULL;
    surfaces_coiffure[SELECTION] = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_coiffure[SELECTION], NULL, SDL_MapRGB(ecran->format, 0, 128, 192));
    SDL_SetAlpha(surfaces_coiffure[SELECTION], SDL_SRCALPHA, 128);

    SDL_Color couleurTexte = {0, 0, 0};
    surfaces_coiffure[TEXTETYPE1] = NULL;
    surfaces_coiffure[TEXTETYPE1] = TTF_RenderText_Blended(police, "COUPE HOMME", couleurTexte);
    surfaces_coiffure[TEXTETYPE2] = NULL;
    surfaces_coiffure[TEXTETYPE2] = TTF_RenderText_Blended(police, "RASAGE", couleurTexte);
    surfaces_coiffure[TEXTETYPE3] = NULL;
    surfaces_coiffure[TEXTETYPE3] = TTF_RenderText_Blended(police, "COUPE BRUSHING", couleurTexte);
    surfaces_coiffure[TEXTETYPE4] = NULL;
    surfaces_coiffure[TEXTETYPE4] = TTF_RenderText_Blended(police, "TECHNIQUE", couleurTexte);
    surfaces_coiffure[TEXTETYPE5] = NULL;
    surfaces_coiffure[TEXTETYPE5] = TTF_RenderText_Blended(police, "COIFFURE", couleurTexte);

    surfaces_coiffure[COMMENTAIRE] = NULL;
    surfaces_coiffure[COMMENTAIRE] = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_coiffure[COMMENTAIRE], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    surfaces_coiffure[TEXTECOMMENTAIRE1] = NULL;
    surfaces_coiffure[TEXTECOMMENTAIRE2] = NULL;

    surfaces_coiffure[TEXTECLIENT] = NULL;

    surfaces_coiffure[OK] = NULL;
    surfaces_coiffure[OK] = SDL_LoadBMP("data/bouton_valider.bmp");
    SDL_SetColorKey(surfaces_coiffure[OK], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));


    surfaces_coiffure[PRECEDENT] = NULL;
    surfaces_coiffure[PRECEDENT] = SDL_LoadBMP("data/bouton_retour.bmp");
    SDL_SetColorKey(surfaces_coiffure[PRECEDENT], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));


}

void afficher_coiffure(SDL_Surface *ecran, SDL_Surface *surfaces_coiffure[NOMBRE_SURFACES_COIFFURE])   {

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 219, 219, 219));

    SDL_Rect position;

    position.x = 150;
    position.y = 100;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);

    position.y = 200;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);

    position.y = 300;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);

    position.y = 400;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);

    position.y = 500;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);

    position.x = 1050;
    position.y = 550;
    SDL_BlitSurface(surfaces_coiffure[OK], NULL, ecran, &position);

    position.x = 1150;
    position.y = 30;
    SDL_BlitSurface(surfaces_coiffure[PRECEDENT], NULL, ecran, &position);

    position.x = 160;
    position.y = 110;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE1], NULL, ecran, &position);

    position.y = 210;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE2], NULL, ecran, &position);

    position.y = 310;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE3], NULL, ecran, &position);

    position.y = 410;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE4], NULL, ecran, &position);

    position.y = 510;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE5], NULL, ecran, &position);

    position.x = 750;
    position.y = 250;
    SDL_BlitSurface(surfaces_coiffure[COMMENTAIRE], NULL, ecran, &position);

    SDL_Flip(ecran);


}


void modifier_commentaire(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], char saisie[50], TTF_Font * police) {

    int i;
    char saisie1[16];
    char saisie2[16];
    SDL_Color couleurTexte = {0, 0, 0};
    SDL_Rect position;
    position.x = 750;
    position.y = 250;
    SDL_BlitSurface(surfaces_coiffure[COMMENTAIRE], NULL, ecran, &position);
    position.x = 760;
    position.y = 280;

    // on cut le char en 2
    for(i = 0; i < 15; i++) {
        saisie1[i] = saisie[i];
    }
    saisie2[0] = '\0';
    for(i = 15; i < strlen(saisie) + 1; i++) {
        saisie2[i - 15] = saisie[i];
    }
    surfaces_coiffure[TEXTECOMMENTAIRE1] = TTF_RenderText_Blended(police, saisie1, couleurTexte);
    SDL_BlitSurface(surfaces_coiffure[TEXTECOMMENTAIRE1], NULL, ecran, &position);
    position.y = 350;
    surfaces_coiffure[TEXTECOMMENTAIRE2] = TTF_RenderText_Blended(police, saisie2, couleurTexte);
    SDL_BlitSurface(surfaces_coiffure[TEXTECOMMENTAIRE2], NULL, ecran, &position);

    SDL_Flip(ecran);

}

void effacer_selection_coiffure(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], int selection_type)   {

    SDL_Rect position;
    position.x = 150;
    position.y = selection_type * 100;
    SDL_BlitSurface(surfaces_coiffure[TYPE], NULL, ecran, &position);
    position.x += 10;
    position.y += 10;
    SDL_BlitSurface(surfaces_coiffure[TEXTETYPE1 + selection_type - 1], NULL, ecran, &position);

    SDL_Flip(ecran);

}

void afficher_selection_coiffure(SDL_Surface * ecran, SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], int selection_type)    {

    SDL_Rect position;
    position.x = 150;
    position.y = selection_type * 100;
    SDL_BlitSurface(surfaces_coiffure[SELECTION], NULL, ecran, &position);
    SDL_Flip(ecran);

}




