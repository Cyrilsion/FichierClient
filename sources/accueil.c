#include "accueil.h"

liste attendre_evenement_accueil(SDL_Surface *ecran, liste li, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], SDL_Surface * surfaces_ajouter[NOMBRE_SURFACES_AJOUTER], SDL_Surface * surfaces_coiffure[NOMBRE_SURFACES_COIFFURE], TTF_Font *police_barre_recherche, TTF_Font *police_resultat_recherche){
    int continuer = 1;
    int nombreRecherche = 0;
    int clientSelect = 0;
    int j;
    int zoom = 0;
    liste recherche[RECHERCHE_MAX];
    liste rescape[RECHERCHE_MAX];
    liste nouvelleListe = NULL;

    int clientsuppr[RECHERCHE_MAX];
    int i = 0;
    char saisie[CARACTERE_MAX];
    saisie[0] = '\0';
    char caractere;
    SDL_Event event;

    ///lancement premiere recherche
    ///initialise les 20 cases de recherche et rescape avec les 20 premiers clients de la liste
    liste lli = li;
    for(int x = 0; x < RECHERCHE_MAX; x++) {
        recherche[x] = lli;
        rescape[x] = NULL;
        if(lli != NULL) lli = lli->suivant;
    }
    modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
    if(recherche[0] != NULL) afficher_selection(clientSelect, ecran, surfaces_accueil[5]);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;

        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
            {


                if(event.button.x >= 1000 && event.button.x <= 1080 && event.button.y >= 40 && event.button.y <= 120)
                {

                    ///on a cliqué sur le bouton coiffure
                    zoom = 0;
                    afficher_coiffure(ecran, surfaces_coiffure);
                    nouvelleListe = attendre_evenement_coiffure(ecran, surfaces_coiffure, recherche[clientSelect], police_barre_recherche);
                    if(nouvelleListe == NULL) continuer = 0;
                    afficher_accueil(ecran, surfaces_accueil);
                    modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
                    if(recherche != NULL) afficher_selection(clientSelect, ecran, surfaces_accueil[5]);

                }
                else if(event.button.x >= 1100 && event.button.x <= 1164 && event.button.y >= 45 && event.button.y <= 109)
                {

                    ///on a cliqué sur le bouton ajouter
                    zoom = 0;
                    afficher_ajouter(ecran, surfaces_ajouter);
                    nouvelleListe = attendre_evenement_ajouter(ecran, surfaces_ajouter, li, police_barre_recherche);
                    if(nouvelleListe == NULL) continuer = 0;
                    else {
                            if(nombreTotal(nouvelleListe) != nombreTotal(li)) {
                                ///si le nouveau client correspond à la recherche on l'ajoute
                                if(strncmp(nouvelleListe->prenom, saisie, strlen(saisie)) == 0 || strncmp(nouvelleListe->nom, saisie, strlen(saisie)) == 0  || strncmp(nouvelleListe->adresse, saisie, strlen(saisie)) == 0) {
                                    int x = 0;
                                    while(recherche[x] != NULL && x < RECHERCHE_MAX) {
                                        x++;
                                    }
                                    if(x < RECHERCHE_MAX) recherche[x] = nouvelleListe;
                                }
                                li = nouvelleListe;
                            }
                    }
                    afficher_accueil(ecran, surfaces_accueil);
                    modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
                    if(recherche[0] != NULL) afficher_selection(clientSelect, ecran, surfaces_accueil[5]);

                }
                else if(event.button.x >= 1180 && event.button.x <= 1280 && event.button.y >= 30 && event.button.y <= 130)
                {

                    ///on a cliqué sur le bouton supprimer
                    if (recherche != NULL)  {

                        li = supprimer_client(li, recherche[clientSelect]);
                        int j = clientSelect;
                        if(recherche[j + 1] == NULL) recherche[j] = NULL;
                        while(recherche[j + 1] != NULL && j < RECHERCHE_MAX) {
                            recherche[j] = recherche[j+1];
                            j++;
                        }
                        recherche[j] = NULL;
                        modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
                        clientSelect = 0;
                        afficher_selection(clientSelect, ecran, surfaces_accueil[5]);

                    }

                }
                else if(event.button.x >= 820 && event.button.x <= 884 && event.button.y >= 250 && event.button.y <= 314)
                {

                   ///on a cliqué sur le bouton zoom
                   blit_zoom(ecran, surfaces_accueil, zoom);
                   if(zoom == 0) {

                        zoom = 1;
                        ///on affiche l'historique du client sélectionné
                        afficher_historique(ecran, recherche, clientSelect, police_resultat_recherche);

                    }
                    else {

                        zoom = 0;

                    }

                }


                else    {

                    while(nombreRecherche < nombreClient(recherche) && nombreRecherche < RECHERCHE_MAX)  {

                        if(event.button.x >= 100 && event.button.x <= 800 && event.button.y >= 150 + nombreRecherche * 30 && event.button.y <= 190 + nombreRecherche * 30)
                        {

                        effacer_selection(ecran, clientSelect, surfaces_accueil, recherche, police_resultat_recherche);
                        clientSelect = nombreRecherche;
                        afficher_selection(clientSelect, ecran, surfaces_accueil[5]);
                        if(zoom == 1)   {
                            SDL_Rect position;
                            position.x = 900;
                            position.y = 150;
                            SDL_BlitSurface(surfaces_accueil[10], NULL, ecran, &position);
                            afficher_historique(ecran, recherche, clientSelect, police_resultat_recherche);
                        }

                        }
                        nombreRecherche++;
                    }
                    nombreRecherche = 0;
                }

            }
            break;

            case SDL_KEYDOWN:
                ///saisie
                if((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z && i < CARACTERE_MAX) || (event.key.keysym.sym==SDLK_SEMICOLON && i < CARACTERE_MAX) || (event.key.keysym.sym==SDLK_SPACE && i < CARACTERE_MAX))    {

                    ///maj barre de recherche
                    caractere = caractere_saisi(event);
                    saisie[i] = caractere;
                    saisie[i + 1] = '\0';
                    SDL_FreeSurface(surfaces_accueil[7]);
                    surfaces_accueil[7] = modifier_texte_recherche(ecran, surfaces_accueil[0], surfaces_accueil[7], saisie, police_barre_recherche);
                    i++;

                    ///maj de la liste de recherche
                    clientsuppr[i - 1] = rechercher_client_update(recherche, rescape, saisie);
                    ///maj resultat recherche
                    clientSelect = 0;
                    modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
                    if(recherche != NULL) afficher_selection(clientSelect, ecran, surfaces_accueil[5]);


                }
                ///Backspace
                else if(event.key.keysym.sym==SDLK_BACKSPACE)   {

                    ///maj barre de recherche
                    i = i -1;
                    if(i < 0) i = 0;
                    saisie[i] = '\0';
                    SDL_FreeSurface(surfaces_accueil[7]);
                    surfaces_accueil[7] = modifier_texte_recherche(ecran, surfaces_accueil[0], surfaces_accueil[7], saisie, police_barre_recherche);

                    ///update liste recherchet et rescape
                    backspace_recherche(recherche, rescape, clientsuppr[i]);

                    ///maj resultat recherche
                    modifier_resultat_recherche(ecran, recherche, surfaces_accueil, police_resultat_recherche);
                    if(recherche != NULL) afficher_selection(clientSelect, ecran, surfaces_accueil[5]);

                }
                ///flèche haut
                else if(event.key.keysym.sym==SDLK_UP && clientSelect > 0)  {

                    effacer_selection(ecran, clientSelect, surfaces_accueil, recherche, police_resultat_recherche);
                    clientSelect --;
                    afficher_selection(clientSelect, ecran, surfaces_accueil[5]);
                    if(zoom == 1)   {
                            SDL_Rect position;
                            position.x = 900;
                            position.y = 150;
                            SDL_BlitSurface(surfaces_accueil[10], NULL, ecran, &position);
                            afficher_historique(ecran, recherche, clientSelect, police_resultat_recherche);
                    }

                }
                ///flèche bas
                else if(event.key.keysym.sym==SDLK_DOWN && clientSelect < (nombreClient(recherche) - 1))   {

                    effacer_selection(ecran, clientSelect, surfaces_accueil, recherche, police_resultat_recherche);
                    clientSelect ++;
                    afficher_selection(clientSelect, ecran, surfaces_accueil[5]);
                    if(zoom == 1)   {
                            SDL_Rect position;
                            position.x = 900;
                            position.y = 150;
                            SDL_BlitSurface(surfaces_accueil[10], NULL, ecran, &position);
                            afficher_historique(ecran, recherche, clientSelect, police_resultat_recherche);
                    }

                }

            break;
        }
    }
    return li;
}

void afficher_accueil(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL])  {

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 219, 219, 219));

    SDL_Rect position;

    position.x = 100;
    position.y = 50;
    SDL_BlitSurface(surfaces_accueil[0], NULL, ecran, &position);

    position.x = 100;
    position.y = 150;
    SDL_BlitSurface(surfaces_accueil[1], NULL, ecran, &position);

    position.x = 1000;
    position.y = 40;
    SDL_BlitSurface(surfaces_accueil[2], NULL, ecran, &position);

    position.x = 1100;
    position.y = 45;
    SDL_BlitSurface(surfaces_accueil[3], NULL, ecran, &position);

    position.x = 1180;
    position.y = 30;
    SDL_BlitSurface(surfaces_accueil[4], NULL, ecran, &position);

    position.x = 110;
    position.y = 55;
    SDL_BlitSurface(surfaces_accueil[7], NULL, ecran, &position);

    position.x = 820;
    position.y = 250;
    SDL_BlitSurface(surfaces_accueil[8], NULL, ecran, &position);

    SDL_Flip(ecran);


}

void initialisation_surfaces_accueil(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], TTF_Font *police_barre_recherche){

    ///barre de recherche blanche
    surfaces_accueil[0] = NULL;
    surfaces_accueil[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///fond blanc pour résultat recherche
    surfaces_accueil[1] = NULL;
    surfaces_accueil[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 550, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///bouton coiffure
    surfaces_accueil[2] = NULL;
    surfaces_accueil[2] = SDL_LoadBMP("data/icone_coiffure.bmp");
    SDL_SetColorKey(surfaces_accueil[2], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///bouton ajouter
    surfaces_accueil[3] = NULL;
    surfaces_accueil[3] = SDL_LoadBMP("data/icone_ajouter_user.bmp");
    SDL_SetColorKey(surfaces_accueil[3], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///bouton supprimer
    surfaces_accueil[4] = NULL;
    surfaces_accueil[4] = SDL_LoadBMP("data/icone_supprimer.bmp");
    SDL_SetColorKey(surfaces_accueil[4], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///selection
    surfaces_accueil[5] = NULL;
    surfaces_accueil[5] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[5], NULL, SDL_MapRGB(ecran->format, 0, 128, 192));
    SDL_SetAlpha(surfaces_accueil[5], SDL_SRCALPHA, 128);
    ///effacer selection
    surfaces_accueil[6] = NULL;
    surfaces_accueil[6] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[6], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///texte rechercher
    SDL_Color couleurTexte = {0, 0, 0};
    surfaces_accueil[7] = NULL;
    if(police_barre_recherche != NULL)
    surfaces_accueil[7] = TTF_RenderText_Blended(police_barre_recherche, "Rechercher...", couleurTexte);
    ///bouton zoom
    surfaces_accueil[8] = NULL;
    surfaces_accueil[8] = SDL_LoadBMP("data/bouton_zoom.bmp");
    SDL_SetColorKey(surfaces_accueil[8], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    /// bouton dezoom
    surfaces_accueil[9] = NULL;
    surfaces_accueil[9] = SDL_LoadBMP("data/bouton_dezoom.bmp");
    SDL_SetColorKey(surfaces_accueil[9], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///cadre blanc historique
    surfaces_accueil[10] = NULL;
    surfaces_accueil[10] = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 550, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[10], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    ///cadre gris historique
    surfaces_accueil[11] = NULL;
    surfaces_accueil[11] = SDL_CreateRGBSurface(SDL_HWSURFACE, 450, 550, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[11], NULL, SDL_MapRGB(ecran->format, 219, 219, 219));
    ///separation verticale
    surfaces_accueil[12] = NULL;
    surfaces_accueil[12] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[12], NULL, SDL_MapRGB(ecran->format, 219, 219, 219));
    ///separation horizontale
    surfaces_accueil[13] = NULL;
    surfaces_accueil[13] = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 5, 32, 0, 0, 0, 0);
    SDL_FillRect(surfaces_accueil[13], NULL, SDL_MapRGB(ecran->format, 219, 219, 219));

}

void afficher_historique(SDL_Surface * ecran, liste recherche[], int clientSelect, TTF_Font * police)    {

   int i;
   SDL_Surface * texte = NULL;
   SDL_Color couleurTexte = {0, 0, 0};
   SDL_Rect position;
   hist hi = NULL;

    position.x = 920;
    position.y = 160;
    hi = recherche[clientSelect]->hist;
    while(hi != NULL) {

        texte = TTF_RenderText_Blended(police, hi->date, couleurTexte);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 1100;
        switch(hi->type)  {
            case 1: texte = TTF_RenderText_Blended(police, "Coupe Homme", couleurTexte);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
            break;
            case 2: texte = TTF_RenderText_Blended(police, "Rasage", couleurTexte);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
            break;
            case 3: texte = TTF_RenderText_Blended(police, "Coupe Brushing", couleurTexte);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
            break;
            case 4: texte = TTF_RenderText_Blended(police, "Technique", couleurTexte);
            SDL_BlitSurface(texte, NULL, ecran, &position);
            break;
            case 5: texte = TTF_RenderText_Blended(police, "Coiffure", couleurTexte);
            SDL_BlitSurface(texte, NULL, ecran, &position);
            break;

        }
        SDL_FreeSurface(texte);
        position.x = 920;
        position.y += 30;
        texte = TTF_RenderText_Blended(police, hi->commentaire, couleurTexte);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);

        position.y += 30;
        hi = hi->suivant;

    }
    SDL_Flip(ecran);
}

SDL_Surface * modifier_texte_recherche(SDL_Surface * ecran, SDL_Surface * barre_clean, SDL_Surface * texte_recherche, char * texte, TTF_Font *police)    {


    SDL_Color couleurTexte = {0, 0, 0};
    SDL_Rect position;
    position.x = 100;
    position.y = 50;
    SDL_BlitSurface(barre_clean, NULL, ecran, &position);
    position.x =110;
    position.y = 55;
    texte_recherche = TTF_RenderText_Blended(police, texte, couleurTexte);
    SDL_BlitSurface(texte_recherche, NULL, ecran, &position);

    SDL_Flip(ecran);

    return texte_recherche;

}

void modifier_resultat_recherche(SDL_Surface * ecran, liste client[], SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], TTF_Font *police)  {

    int i = 0;
    SDL_Rect position;
    position.x = 100;
    position.y = 150;
    SDL_BlitSurface(surfaces_accueil[1], NULL, ecran, &position);

     while  (client[i] != NULL && i < RECHERCHE_MAX)  {

        blitTexteRecherche(ecran, position, surfaces_accueil, client[i], police);
        position.y += 30;
        i++;
    }

}

void blitTexteRecherche(SDL_Surface * ecran, SDL_Rect position,SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], liste client, TTF_Font *police)   {

        SDL_Color couleurTexte = {0, 0, 0};
        SDL_Surface * texte_resultat_recherche = NULL;

        ///afficher prenom
        position.x = 110;
        texte_resultat_recherche = TTF_RenderText_Blended(police, client->prenom, couleurTexte);
        SDL_BlitSurface(texte_resultat_recherche, NULL, ecran, &position);

        position.x = 250;
        SDL_BlitSurface(surfaces_accueil[12], NULL, ecran, &position);

        ///afficher nom
        position.x = 260;
        SDL_FreeSurface(texte_resultat_recherche);
        texte_resultat_recherche = TTF_RenderText_Blended(police, client->nom, couleurTexte);
        SDL_BlitSurface(texte_resultat_recherche, NULL, ecran, &position);

        position.x = 400;
        SDL_BlitSurface(surfaces_accueil[12], NULL, ecran, &position);

        ///afficher adresse
        position.x = 410;
        SDL_FreeSurface(texte_resultat_recherche);
        texte_resultat_recherche = TTF_RenderText_Blended(police, client->adresse, couleurTexte);
        SDL_BlitSurface(texte_resultat_recherche, NULL, ecran, &position);

        ///afficher barre horiozontale
        position.x = 100;
        position.y += 25;
        SDL_BlitSurface(surfaces_accueil[13], NULL, ecran, &position);

        SDL_Flip(ecran);
}

void effacer_selection(SDL_Surface * ecran, int clientSelect, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], liste client[], TTF_Font * police) {

    SDL_Rect position;
    position.x = 100;
    position.y = 150 + clientSelect * 30;
    SDL_BlitSurface(surfaces_accueil[6], NULL, ecran, &position);
    position.x = 110;
    blitTexteRecherche(ecran, position, surfaces_accueil, client[clientSelect], police);

}

void afficher_selection(int clientSelect, SDL_Surface * ecran, SDL_Surface * selection)   {


    SDL_Rect position;
    position.x = 100;
    position.y = 150 + clientSelect * 30;
    SDL_BlitSurface(selection, NULL, ecran, &position);
    SDL_Flip(ecran);


}

void blit_zoom(SDL_Surface * ecran, SDL_Surface * surfaces_accueil[NOMBRE_SURFACES_ACCUEIL], int zoom)  {

    SDL_Rect position;
    if(zoom == 0)   {
        ///on blit le zoom-
        position.x = 820;
        position.y = 250;
        SDL_BlitSurface(surfaces_accueil[9], NULL, ecran, &position);
        ///on blit la surface blanche
        position.x = 900;
        position.y = 150;
        SDL_BlitSurface(surfaces_accueil[10], NULL, ecran, &position);
    }
    else    {
        ///on blit la surface grise
        position.x = 800;
        position.y = 150;
        SDL_BlitSurface(surfaces_accueil[11], NULL, ecran, &position);
        ///on blit le zoom+
        position.x = 820;
        position.y = 250;
        SDL_BlitSurface(surfaces_accueil[8], NULL, ecran, &position);
    }
    SDL_Flip(ecran);
}


