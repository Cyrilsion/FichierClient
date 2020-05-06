#ifndef GRAPHIQUE_H_INCLUDED
#define GRAPHIQUE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#define FICHIER "data/base.txt"
#define NOMBRE_SURFACES_ACCUEIL 14
#define NOMBRE_SURFACES_AJOUTER 11
#define NOMBRE_SURFACES_COIFFURE 13
#define RECHERCHE_MAX 15
#define CARACTERE_MAX 20

struct historique
{

    int type;
    char * date;
    char * commentaire;
    struct historique * suivant;

};
typedef struct historique * hist;

struct liste_client
{


    char * prenom;
    char* nom;
    char * tel;
    char * adresse;
    int points;
    struct historique * hist;
    struct liste_client * suivant;



};
typedef struct liste_client * liste;

enum    {CHAMPSAISIE, VALIDER, RETOUR, TEXTEPRENOM, TEXTENOM, TEXTETEL, TEXTEVILLE, PRENOM, NOM, TEL, VILLE};

enum    {TYPE, SELECTION, TEXTETYPE1, TEXTETYPE2, TEXTETYPE3, TEXTETYPE4, TEXTETYPE5, COMMENTAIRE, TEXTECOMMENTAIRE1,TEXTECOMMENTAIRE2, TEXTECLIENT, OK, PRECEDENT};

enum    {LISTE_RECHERCHE, LISTE_RESCAPE};

int notPresent(liste li, char * prenom1, char * nom1, char * adresse1);
liste ajouter_client(liste li, char * prenom1, char * nom1, char * tel1, char * adresse1, int points1, hist hi);
hist ajout_hist(hist hi, int type, char * date, char * commentaire);
liste ajouter_historique(liste client, int type, char * commentaire);
liste ajouter_client_recherche(liste li, char * prenom1, char * nom1, char * adresse1);
void backspace_recherche(liste recherche[], liste rescape[], int nombreRescape);
int rechercher_client_update(liste recherche[], liste rescape[], char * saisie);
liste supprimer_client(liste li, liste clientASuppr);
liste supprimer_client_rech(liste recherche[], int clientSelect);
liste initialisation(liste li);
void enregistrer(liste li);
char * inttochar(int n);
int nombreClient(liste client[]);
int nombreClientRech(liste client);
char caractere_saisi(SDL_Event event);


#endif // GRAPHIQUE_H_INCLUDED
