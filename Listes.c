/*
 * Auteurs : Imane ERRAHMANI, Sarah ENG
 * Creation : 08-03-2022
 * Modification : 19-03-2022
 */
#include "Listes.h"

/* Fonction qui alloue une cellule, et si l'allocation a reussi elle renvoie son adresse, sinon NULL.
 * S'il n'y a aucun probleme d'allocation, elle initialise le champ mot par la chaine de caractere reçue
 * en parametre, et le champ suivant par NULL.
 */
Cellule* allouer_Cellule(char *mot) {
    Cellule *tmp;
    char *tab;
    /* Allocation de la cellule */
    tmp = (Cellule *)malloc(sizeof(Cellule));
    /* Allocation de la chaine de caractere pour la cellule */
    tab = (char *)malloc(sizeof(char) * strlen(mot) + 1);
    /* Si une des deux allocations a echoue, on renvoie NULL */
    if (tmp == NULL || tab == NULL)
        return NULL;
    /* Copie du mot dans le tableau de caracteres tab */
    strcpy(tab, mot);
    /* Initialisation des champs de la cellule et renvoie de son adresse */
    tmp->mot = tab;
    tmp->suivant = NULL;
    return tmp;
}

/* Fonction qui insere en tete de la liste L la chaine de caracteres mot.
 * Elle renvoie 1 si l'insertion a ete effectuee, et 0 s'il y a eu un probleme.
 */
int inserer_en_tete(Liste *L, char *mot) {
    Cellule *tmp;
    tmp = allouer_Cellule(mot);
    /* S'il y a eu un probleme d'allocation, on renvoie 0 */
    if (tmp == NULL)
        return 0;
    /* Insertion de la cellule qui contient le nouveau mot, en tete de la liste */
    tmp->suivant = *L;
    *L = tmp;
    return 1;
}

/* Fonction qui renvoie 1 si le mot est deja present dans la liste, et 0 sinon.
 */
int appartient(Liste L, char *mot) {
    Cellule *tmp = L;
    /* Parcours de la liste */
    while(tmp) {
        /* Si le mot est present dans la liste, on renvoie 1 */
        if(strcmp(tmp->mot, mot) == 0) {
            return 1;
        }
        tmp = tmp->suivant;
    }
    return 0;
}

/* Fonction qui libere l'espace memoire dedie à tous les elements de la liste.
 */
void liberer_Liste(Liste* L) {
    Liste next, courant;
    courant = *L;
    /* Parcours et liberation de la memoire de la cellule */
    while(courant) {
        next = courant->suivant;
        free(courant);
        courant = next;
    }
}

/* Fonction qui affiche, un par ligne, tous les elements de la liste.
 */
void afficher_Liste(Liste L) {
    /* Parcours de la liste et affichage du mot de la cellule */
    while(L) {
        printf("%s \n", L->mot);
        L = L->suivant;
    }
    printf("\n");
}
