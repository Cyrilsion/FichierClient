#include "data.h"


liste ajouter_client(liste li, char * prenom1, char * nom1, char * tel1, char * adresse1, int points1){


    liste lli;
    lli = (liste)malloc(sizeof(struct liste_client));
    lli->prenom = strdup(prenom1);
    lli->nom = strdup(nom1);
    lli->tel = strdup(tel1);
    lli->adresse = strdup(adresse1);
    lli->points = points1;
    lli->hist = NULL;
    lli->suivant = li;
    return lli;



}

hist ajout_hist(hist hi, int type, char * date, char * commentaire)   {

    hist temp = NULL;
    temp = (hist)malloc(sizeof(struct historique));
    temp->type = type;
    temp->date = strdup(date);
    temp->commentaire = strdup(commentaire);

    temp->suivant = hi;

    return temp;

}

liste ajouter_historique(liste client, int type, char * commentaire)    {

    if(client != NULL)   {

        time_t timestamp = time( NULL );
        struct tm * pTime = localtime( & timestamp );
        char date[20];
        strftime( date, 50, "%d/%m/%Y %Hh%M", pTime );
        date[16] = '\0';
        client->hist = ajout_hist(client->hist, type, date, commentaire);
    }

}

void backspace_recherche(liste recherche[], liste rescape[], int nombreRescape) {

    int i = 0;
    int j = 0;
    ///on va à la fin des deux listes
    while(recherche[i] != NULL) {
        i++;
    }
    while(rescape[j] != NULL) {
        j++;
    }
    if(j > 0) j--;
    /// on déplace rescape vers recherche
    while(nombreRescape > 0) {
        /// on ajoute dans recherche
        recherche[i] = rescape[j];
        ///on supprime dans rescape
        rescape[j] = NULL;

        i++;
        j--;
        nombreRescape--;

    }
}

int rechercher_client_update(liste recherche[], liste rescape[], char * saisie) {

    int  i, j;
    int clientSuppr = 0;
    while(recherche[i] != NULL && i < RECHERCHE_MAX) {

        ///aucun des attributs ne correspond
        if(strncmp(recherche[i]->prenom, saisie, strlen(saisie)) != 0 && strncmp(recherche[i]->nom, saisie, strlen(saisie)) != 0  && strncmp(recherche[i]->adresse, saisie, strlen(saisie)) != 0) {
            ///on ajoute à la liste des rescapes
            j = 0;
            while(rescape[j] != NULL) {
                j++;
            }
            rescape[j] = recherche[i];
            ///on supprime de la liste de recherche
            j = i;
            while(recherche[j + 1] != NULL && j < RECHERCHE_MAX) {
                recherche[j] = recherche[j+1];
                j++;
            }
            recherche[j] = NULL;
            clientSuppr++;
        }
        else i++;

    }

    return clientSuppr;

}

liste supprimer_client(liste li, liste clientASuppr){

    liste temp = NULL;
    ///c'est le premier de la liste
    if(li == clientASuppr) {
        temp = li->suivant;
        free(li);
        return temp;
    }
    else {
        temp = li;
        while(temp->suivant != clientASuppr && temp->suivant != NULL) {
            temp = temp->suivant;
        }
        ///on l'a trouvé
        if(temp->suivant == clientASuppr) {
            liste lli = temp->suivant;
            temp->suivant = temp->suivant->suivant;
            free(lli);
        }
        ///on est arrivés à la fin
        return li;
    }

}

liste initialisation(liste li){


    FILE* fichier = NULL;
    fichier = fopen(FICHIER,"r");
    if(fichier != NULL)
    {

        //on initialise la liste
        char prenom[20], nom[20], tel[15], adresse[50], date[10], commentaire[50], caractere;
        int points =0;
        int type = 0;
        int compteur = 0;
        hist temp = NULL;
        caractere = fgetc(fichier);


        while (caractere != EOF)
        {


            while (caractere != '|')
            {

                prenom[compteur] = caractere;
                compteur ++;
                caractere = fgetc(fichier);

            }

            prenom[compteur] = '\0';
            compteur = 0;
            caractere = fgetc(fichier);

            while (caractere != '|')
            {

                nom[compteur] = caractere;
                compteur ++;
                caractere = fgetc(fichier);


            }

            nom[compteur] = '\0';
            compteur = 0;
            caractere = fgetc(fichier);


            while (caractere != '|')
            {

                tel[compteur] = caractere;
                compteur ++;
                caractere = fgetc(fichier);
            }

            tel[compteur] = '\0';
            compteur = 0;
            caractere = fgetc(fichier);


            while (caractere != '|')
            {

                adresse[compteur] = caractere;
                compteur ++;
                caractere = fgetc(fichier);
            }

            adresse[compteur] = '\0';
            caractere = fgetc(fichier);
            compteur = 0;

            while   (caractere != '|') {

                points += caractere - '0';
                caractere = fgetc(fichier);

            }

            li = ajouter_client(li, prenom, nom, tel, adresse, points);
            caractere = fgetc(fichier);

            while(caractere != '\n') {

                while   (caractere != '|') {

                    type += caractere - '0';
                    caractere = fgetc(fichier);

                }

                    caractere = fgetc(fichier);

                while (caractere != '|')
                {

                    date[compteur] = caractere;
                    compteur ++;
                    caractere = fgetc(fichier);
                }
                date[compteur] = '\0';
                caractere = fgetc(fichier);
                compteur = 0;

                while (caractere != '|')
                {

                    commentaire[compteur] = caractere;
                    compteur ++;
                    caractere = fgetc(fichier);
                }
                commentaire[compteur] = '\0';
                temp = ajout_hist(temp, type, date, commentaire);
                caractere = fgetc(fichier);
                compteur = 0;

             }

            li->hist = temp;
            caractere = fgetc(fichier);

        }

        fclose(fichier);
        printf("Chargement réussi!");
        return li;

    }

    else
    {

        printf("Aucun fichier chargé. Il n'y a peut-être encore aucun client d'ajouté. \n");
        return NULL;

    }


}

void enregistrer(liste li){

    FILE* fichier = NULL;
    fichier = fopen(FICHIER,"w+");

    while (li != NULL)
    {

        fputs(li->prenom, fichier);
        fputc('|',fichier);
        fputs(li->nom, fichier);
        fputc('|',fichier);
        fputs(li->tel, fichier);
        fputc('|',fichier);
        fputs(li->adresse, fichier);
        fputc('|',fichier);
        fprintf(fichier, "%d", li->points);
        fputc('|',fichier);
        if(li->hist != NULL)    {
            // inserer l'historique
            while(li->hist != NULL) {
                fprintf(fichier, "%d", li->hist->type);
                fputc('|',fichier);
                fputs(li->hist->date, fichier);
                fputc('|',fichier);
                fputs(li->hist->commentaire, fichier);
                fputc('|',fichier);
                li->hist = li->hist->suivant;
            }
        }
        fputc('\n', fichier);
        li = li->suivant;


    }
    fclose(fichier);
    printf("Enregistrement reussi! \n");

}

char * inttochar(int n)  {

        char * str = NULL;
        int s = 0, i = n;
        while(i)
            i/=10, s++;

        str = malloc((s+1) * sizeof(char));
        if (str == NULL) return NULL;
        for (i = s-1; i >=0 ; i--, n/=10)
            str[i] = n % 10 + '0';
        str[s] = '\0';
        return str;


}

int nombreClient(liste client[])  {

    int i = 0;
    while(client[i] != NULL) {
        i++;
    }
    return i;

}

int nombreTotal(liste client) {

    int i = 0;
    while(client != NULL) {

        i++;
        client = client->suivant;

    }
    return i;
}

char caractere_saisi(SDL_Event event){

    char caractere;
                switch(event.key.keysym.sym)    {
                    case SDLK_a:
                        caractere = 'q';
                        break;
                    case SDLK_b:
                        caractere = 'b';
                        break;
                    case SDLK_c:
                        caractere = 'c';
                        break;
                    case SDLK_d:
                        caractere = 'd';
                        break;
                    case SDLK_e:
                        caractere = 'e';
                        break;
                    case SDLK_f:
                        caractere = 'f';
                        break;
                    case SDLK_g:
                        caractere = 'g';
                        break;
                    case SDLK_h:
                        caractere = 'h';
                        break;
                    case SDLK_i:
                        caractere = 'i';
                        break;
                    case SDLK_j:
                        caractere = 'j';
                        break;
                    case SDLK_k:
                        caractere = 'k';
                        break;
                    case SDLK_l:
                        caractere = 'l';
                        break;
                    case SDLK_SEMICOLON:
                        caractere = 'm';
                        break;
                    case SDLK_n:
                        caractere = 'n';
                        break;
                    case SDLK_o:
                        caractere = 'o';
                        break;
                    case SDLK_p:
                        caractere = 'p';
                        break;
                    case SDLK_q:
                        caractere = 'a';
                        break;
                    case SDLK_r:
                        caractere = 'r';
                        break;
                    case SDLK_s:
                        caractere = 's';
                        break;
                    case SDLK_t:
                        caractere = 't';
                        break;
                    case SDLK_u:
                        caractere = 'u';
                        break;
                    case SDLK_v:
                        caractere = 'v';
                        break;
                    case SDLK_w:
                        caractere = 'z';
                        break;
                    case SDLK_x:
                        caractere = 'x';
                        break;
                    case SDLK_y:
                        caractere = 'y';
                        break;
                    case SDLK_z:
                        caractere = 'w';
                        break;
                    case SDLK_BACKSPACE:
                        caractere = '<';
                        break;
                    case SDLK_SPACE:
                        caractere = ' ';
                        break;
                    case SDLK_0:
                        caractere = '0';
                        break;
                    case SDLK_1:
                        caractere = '1';
                        break;
                    case SDLK_2:
                        caractere = '2';
                        break;
                    case SDLK_3:
                        caractere = '3';
                        break;
                    case SDLK_4:
                        caractere = '4';
                        break;
                    case SDLK_5:
                        caractere = '5';
                        break;
                    case SDLK_6:
                        caractere = '6';
                        break;
                    case SDLK_7:
                        caractere = '7';
                        break;
                    case SDLK_8:
                        caractere = '8';
                        break;
                    case SDLK_9:
                        caractere = '9';
                        break;
                    case SDLK_KP0:
                        caractere = '0';
                        break;
                    case SDLK_KP1:
                        caractere = '1';
                        break;
                    case SDLK_KP2:
                        caractere = '2';
                        break;
                    case SDLK_KP3:
                        caractere = '3';
                        break;
                    case SDLK_KP4:
                        caractere = '4';
                        break;
                    case SDLK_KP5:
                        caractere = '5';
                        break;
                    case SDLK_KP6:
                        caractere = '6';
                        break;
                    case SDLK_KP7:
                        caractere = '7';
                        break;
                    case SDLK_KP8:
                        caractere = '8';
                        break;
                    case SDLK_KP9:
                        caractere = '9';
                        break;
                    }
    return caractere;
}


