#include "ajouter_client.h"

liste attendre_evenement_ajouter(SDL_Surface * ecran, SDL_Surface * surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], liste li, TTF_Font * police_barre_recherche)    {


    char saisie_prenom[20], saisie_nom[20], saisie_tel[11], saisie_ville[50];
    int champ_saisie = 0;
    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);
    int i[4] = {0};
    char caractere;
    SDL_Event event;

    while (1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            return NULL;
            break;

        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(event.button.x >= 300 && event.button.x <= 1000 && event.button.y >= 100 && event.button.y <= 150)
                {
                    //saisie prenom
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                    champ_saisie = 0;
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

                }
                if(event.button.x >= 300 && event.button.x <= 1000 && event.button.y >= 200 && event.button.y <= 250)
                {
                    //saisie nom
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                    champ_saisie = 1;
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

                }
                if(event.button.x >= 300 && event.button.x <= 1000 && event.button.y >= 300 && event.button.y <= 350)
                {
                    //saisie tel
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                    champ_saisie = 2;
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

                }
                if(event.button.x >= 300 && event.button.x <= 1000 && event.button.y >= 400 && event.button.y <= 450)
                {
                    //saisie ville
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                    champ_saisie = 3;
                    drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

                }
                if(event.button.x >= 1050 && event.button.x <= 1178 && event.button.y >= 550 && event.button.y <= 614)
                {

                    //valider
                    li = ajouter_client(li, saisie_prenom, saisie_nom, saisie_tel, saisie_ville, 0);
                    return li;

                }
                if(event.button.x >= 1150 && event.button.x <= 1214 && event.button.y >= 30 && event.button.y <= 94)
                {

                    //retour
                    return li;

                }
            }
            break;
        case SDL_KEYDOWN:

            if((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z ) || event.key.keysym.sym==SDLK_SEMICOLON || event.key.keysym.sym==SDLK_BACKSPACE || event.key.keysym.sym == SDLK_SPACE || (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) || (event.key.keysym.sym >= SDLK_KP0 && event.key.keysym.sym <= SDLK_KP9))    {

                caractere = caractere_saisi(event);
                    //remplis le bon champs
                    if (caractere == '<')    {

                        i[champ_saisie] = i[champ_saisie] - 2;
                        if(i[champ_saisie] < -1) i[champ_saisie] = -1;

                    }
                    if((champ_saisie == 0 && i[0] < 19) || (champ_saisie == 1 && i[1] < 19) || (champ_saisie == 2 && i[2] < 10) || (champ_saisie == 3 && i[3] < 49))    {
                        switch(champ_saisie)    {

                        case 0:
                            if (caractere != '<') saisie_prenom[i[0]] = caractere;
                            saisie_prenom[i[0] + 1] = '\0';
                            SDL_FreeSurface(surfaces_ajouter[champ_saisie + 3]);
                            surfaces_ajouter[champ_saisie + 3] = modifier_champ_ajouter(ecran, surfaces_ajouter[champ_saisie + 3], surfaces_ajouter[CHAMPSAISIE], saisie_prenom, champ_saisie, police_barre_recherche);
                            break;
                        case 1:
                            if (caractere != '<') saisie_nom[i[1]] = caractere;
                            saisie_nom[i[1] + 1] = '\0';
                            SDL_FreeSurface(surfaces_ajouter[champ_saisie + 3]);
                            surfaces_ajouter[champ_saisie + 3] = modifier_champ_ajouter(ecran, surfaces_ajouter[champ_saisie + 3], surfaces_ajouter[CHAMPSAISIE], saisie_nom, champ_saisie, police_barre_recherche);
                            break;
                        case 2:
                            if (caractere != '<') saisie_tel[i[2]] = caractere;
                            saisie_tel[i[2] + 1] = '\0';
                            SDL_FreeSurface(surfaces_ajouter[champ_saisie + 3]);
                            surfaces_ajouter[champ_saisie + 3] = modifier_champ_ajouter(ecran, surfaces_ajouter[champ_saisie + 3], surfaces_ajouter[CHAMPSAISIE], saisie_tel, champ_saisie, police_barre_recherche);
                            break;
                        case 3:
                            if (caractere != '<') saisie_ville[i[3]] = caractere;
                            saisie_ville[i[3] + 1] = '\0';
                            SDL_FreeSurface(surfaces_ajouter[champ_saisie + 3]);
                            surfaces_ajouter[champ_saisie + 3] = modifier_champ_ajouter(ecran, surfaces_ajouter[champ_saisie + 3], surfaces_ajouter[CHAMPSAISIE], saisie_ville, champ_saisie, police_barre_recherche);
                            break;

                        }
                        i[champ_saisie]++;
                    }
                }
            if(event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_TAB)   {

                drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                champ_saisie ++;
                if(champ_saisie > 3)    champ_saisie = 0;
                drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

            }
            if(event.key.keysym.sym==SDLK_UP)   {

                drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 255, 255, 255);
                champ_saisie --;
                if(champ_saisie < 0)    champ_saisie = 3;
                drawEmptyRect(ecran, 300, 100 + champ_saisie* 100, 700, 50, 10, 170, 231);

            }
            if(event.key.keysym.sym==SDLK_RETURN)   {

                //valider
                li = ajouter_client(li, saisie_prenom, saisie_nom, saisie_tel, saisie_ville, 0);
                return li;

            }
            if(event.key.keysym.sym==SDLK_ESCAPE)   {

                //retour
                return li;

            }
            break;

        }

    }
}

void initialisation_surfaces_ajouter(SDL_Surface *ecran, SDL_Surface *surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], TTF_Font * police)  {

    surfaces_ajouter[CHAMPSAISIE] = NULL;
    surfaces_ajouter[CHAMPSAISIE] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_ajouter[CHAMPSAISIE], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    surfaces_ajouter[VALIDER] = NULL;
    surfaces_ajouter[VALIDER] = SDL_LoadBMP("data/bouton_valider.bmp");
    SDL_SetColorKey(surfaces_ajouter[VALIDER], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));


    surfaces_ajouter[RETOUR] = NULL;
    surfaces_ajouter[RETOUR] = SDL_LoadBMP("data/bouton_retour.bmp");
    SDL_SetColorKey(surfaces_ajouter[RETOUR], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));


    surfaces_ajouter[TEXTEPRENOM] = NULL;
    surfaces_ajouter[TEXTENOM] = NULL;
    surfaces_ajouter[TEXTETEL] = NULL;
    surfaces_ajouter[TEXTEVILLE] = NULL;

    SDL_Color couleurTexte = {0, 0, 0};
    surfaces_ajouter[PRENOM] = NULL;
    surfaces_ajouter[NOM] = NULL;
    surfaces_ajouter[TEL] = NULL;
    surfaces_ajouter[VILLE] = NULL;
    if(police != NULL)  {

        surfaces_ajouter[PRENOM] = TTF_RenderText_Blended(police, "PRENOM", couleurTexte);
        surfaces_ajouter[NOM] = TTF_RenderText_Blended(police, "NOM", couleurTexte);
        surfaces_ajouter[TEL] = TTF_RenderText_Blended(police, "TELEPHONE", couleurTexte);
        surfaces_ajouter[VILLE] = TTF_RenderText_Blended(police, "ADRESSE", couleurTexte);

    }

}

void afficher_ajouter(SDL_Surface *ecran, SDL_Surface *surfaces_ajouter[NOMBRE_SURFACES_AJOUTER])   {

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 219, 219, 219));

    SDL_Rect position;

    position.x = 300;
    position.y = 100;
    SDL_BlitSurface(surfaces_ajouter[CHAMPSAISIE], NULL, ecran, &position);

    position.y = 200;
    SDL_BlitSurface(surfaces_ajouter[CHAMPSAISIE], NULL, ecran, &position);

    position.y = 300;
    SDL_BlitSurface(surfaces_ajouter[CHAMPSAISIE], NULL, ecran, &position);

    position.y = 400;
    SDL_BlitSurface(surfaces_ajouter[CHAMPSAISIE], NULL, ecran, &position);

    position.x = 1050;
    position.y = 550;
    SDL_BlitSurface(surfaces_ajouter[VALIDER], NULL, ecran, &position);

    position.x = 1150;
    position.y = 30;
    SDL_BlitSurface(surfaces_ajouter[RETOUR], NULL, ecran, &position);

    position.x = 50;
    position.y = 100;
    SDL_BlitSurface(surfaces_ajouter[PRENOM], NULL, ecran, &position);

    position.y = 200;
    SDL_BlitSurface(surfaces_ajouter[NOM], NULL, ecran, &position);

    position.y = 300;
    SDL_BlitSurface(surfaces_ajouter[TEL], NULL, ecran, &position);

    position.y = 400;
    SDL_BlitSurface(surfaces_ajouter[VILLE], NULL, ecran, &position);

    SDL_Flip(ecran);


}

void drawEmptyRect(SDL_Surface * surf,int posX, int posY, int width, int length, int R, int G, int B)   {
	SDL_Rect ligneHaut;
	ligneHaut.x = posX - 5;
	ligneHaut.y = posY - 5;
	ligneHaut.w = width + 10;
	ligneHaut.h = 5;

	SDL_FillRect(surf, &ligneHaut, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneDroite;
	ligneDroite.x = posX+width;
	ligneDroite.y = posY - 5;
	ligneDroite.w = 5;
	ligneDroite.h = length + 10;

	SDL_FillRect(surf, &ligneDroite, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneGauche;
	ligneGauche.x = posX - 5;
	ligneGauche.y = posY - 5;
	ligneGauche.w = 5;
	ligneGauche.h = length + 10;

	SDL_FillRect(surf, &ligneGauche, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneBas;
	ligneBas.x = posX - 5;
	ligneBas.y = posY+length;
	ligneBas.w = width + 10;
	ligneBas.h = 5;

	SDL_FillRect(surf, &ligneBas, SDL_MapRGB(surf->format, R, G, B));
	SDL_Flip(surf);
}


SDL_Surface * modifier_texte_client(SDL_Surface * ecran, SDL_Surface * texteClient, liste client, TTF_Font * police)   {

    char * texte;
    texte = malloc(50 * sizeof(char));
    if(client == NULL)  strcpy(texte, "Aucun client sélectionné");
    else  {

        strcpy(texte, client->prenom);
        strcat(texte, "  ");
        strcat(texte, client->nom);

    }
    SDL_Color couleurTexte = {0, 0, 0};
    SDL_Rect position;
    position.x = 750;
    position.y = 120;
    texteClient = TTF_RenderText_Blended(police, texte, couleurTexte);
    SDL_BlitSurface(texteClient, NULL, ecran, &position);
    SDL_Flip(ecran);

    free(texte);

    return texteClient;

}

SDL_Surface * modifier_champ_ajouter(SDL_Surface * ecran, SDL_Surface * champAmodifier, SDL_Surface * blanc, char * texte, int champ_saisie, TTF_Font * police) {

    SDL_Color couleurTexte = {0, 0, 0};
    SDL_Rect position;
    position.x = 300;
    position.y = 100 + 100 * champ_saisie;
    SDL_BlitSurface(blanc, NULL, ecran, &position);

    position.x = 300;
    position.y = 110 + 100 * champ_saisie;
    champAmodifier = TTF_RenderText_Blended(police, texte, couleurTexte);
    SDL_BlitSurface(champAmodifier, NULL, ecran, &position);

    SDL_Flip(ecran);

    return champAmodifier;

}


