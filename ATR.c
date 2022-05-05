/*
 * Auteurs : Imane ERRAHMANI, Sarah ENG
 * Creation : 08-03-2022
 * Modification : 20-03-2022
 */
#include "ATR.h"

/* Fonction qui cree et renvoie un ATR vide.
 */
ATR creer_ATR_vide() {
    ATR tmp = NULL;
    return tmp;
}

/* Fonction qui libere l'espace memoire dedie à tous les elements de l'ATR.
 */
void liberer_ATR(ATR *A) {
    /* Liberation recursive sur le sous-arbre gauche */
    if ((*A)->gauche) {
        liberer_ATR(&((*A)->gauche));
    }
    /* Liberation recursive sur le sous-arbre fils */
    if ((*A)->fils) {
        liberer_ATR(&((*A)->fils));
    }
    /* Liberation recursive sur le sous-arbre droit */
    if ((*A)->droit) {
        liberer_ATR(&((*A)->droit));
    }
    /* Si c'est une feuille, on libere l'espace memoire */
    free(*A);
    *A = NULL;
}

/* Fonction prive qui alloue un noeud, et si l'allocation a reussi elle renvoie son adresse, sinon NULL.
 * S'il n'y a aucun probleme d'allocation, elle initialise le champ lettre par le caractere c reçu
 * en parametre, et les champs gauche, fils et droit par NULL.
 */
ATR alloue_noeud (char c){
    /* Allocation du noeud */
    ATR noeud = (ATR)malloc(sizeof(Noeud));
    /* Si l'allocation a reussi */
    if (noeud) {
        /* Conversion en minuscule de la lettre si c'est une majuscule, et initialisation du champ lettre */
        if ('A' <= c && c <= 'Z'){
            noeud->lettre = c - 'A' + 'a';
        }
        else {
            noeud->lettre = c;
        }
        /* Initialisation des champs droit, fils et gauche */
        noeud->droit = NULL;
        noeud->fils = NULL;
        noeud->gauche = NULL;
    }
    return noeud;
}

/* Fonction prive qui ajoute le mot, lettre par lettre, dans l'ATR.
 */
void ajoute_branche (ATR* A, char* mot) {
    /* Si l'allocation du noeud a reussi */
    if ((*A = alloue_noeud(*mot)) != NULL){
        /* Si la chaine de caracteres mot n'est pas vide */
        if (*mot != '\0'){
            /* Ajout recursif lettre par lettre dans le sous-arbre fils */
            ajoute_branche(&((*A)->fils), mot + 1);
        }
    }
}

/* Fonction qui renvoie 1 si l'ajout du mot dans l'ATR a reussi, et 0 sinon.
 */
int inserer_dans_ATR (ATR *A, char* mot){
    /* Si le noeud est vide, on insere directement le mot */
    if ((*A) == NULL){
        ajoute_branche(A, mot);
        return 1;
    }
    else {
        /* Insertion à gauche si la lettre actuelle est superieure à la premiere lettre du mot */
        if((*A)->lettre > *mot){
            inserer_dans_ATR(&((*A)->gauche), mot);
            return 1;
        }
        /* Insertion à droite si la lettre actuelle est inferieure à la premiere lettre du mot */
        else if((*A)->lettre < *mot){
            inserer_dans_ATR(&((*A)->droit), mot);
            return 1;
        }
        else {
            /* Insertion dans le fils si la lettre actuelle est egale à la premiere lettre du mot, et que le mot n'est pas fini */
            if ((*A)->lettre == *mot && *mot != '\0') {
                inserer_dans_ATR(&((*A)->fils), mot + 1);
                return 1;
            }
        }
    }
    return 0;
    
}

/* Fonction prive qui affiche les mots de l'ATR.
 */
void afficher_ATR_aux (ATR A, char buffer[], int indice) {
    /* Si le noeud est vide, il n'y a plus rien à afficher */
    if (A == NULL) {
        return;
    }
    if (A) {
        /* Si le sous-arbre gauche n'est pas vide, on l'affiche */
        if (A->gauche){
            afficher_ATR_aux(A->gauche, buffer, indice);
        }
        /* Insertion de la lettre dans la chaine de caracteres */
        buffer[indice] = A->lettre;
        /* Si c'est la fin du mot, on insere le caractere de fin de mot dans la chaine et on l'affiche */
        if (A->lettre == '\0'){
            buffer[indice + 1] = '\0';
            printf("%s \n", buffer);
        }
        /* Si le sous-arbre fils n'est pas vide, on l'affiche */
        if (A->fils){
            afficher_ATR_aux(A->fils, buffer, indice + 1);
        }
        /* Si le sous-arbre droit n'est pas vide, on l'affiche */
        if (A->droit){
            afficher_ATR_aux(A->droit, buffer, indice);
        }
        
    }
}

/* Fonction qui affiche les mots de l'ATR.
 */
void afficher_ATR (ATR A) {
    char buffer[TAILLE_MOT];
    int courant = 0;
    afficher_ATR_aux(A, buffer, courant);
}

/* Fonction qui renvoie 1 si le mot est dans l'ATR, et 0 sinon.
 */
int recherche_ATR (ATR A, char *mot) {
    /* Si on a atteint une feuille, alors on n'a pas trouve le mot */
    if (A == NULL) {
        return 0;
    }
    /* Si la premiere lettre du mot est egale à la lettre du noeud actuel */
    if (*mot == A->lettre) {
        /* Et que c'est la fin du mot, alors le mot est dans l'ATR */
        if (*mot == '\0'){
            return 1;
        }
        /* Sinon, le mot n'est pas termine, donc on cherche dans le fils */
        return recherche_ATR(A->fils, mot + 1);
    }
    /* Si la premiere lettre du mot est inferieure à la lettre du noeud, on cherche à gauche */
    else if (*mot < A->lettre) {
        return recherche_ATR(A->gauche, mot);
    }
    /* Si la premiere lettre du mot est superieur à la lettre du noeud, on cherche à droite */
    else if (*mot > A->lettre) {
        return recherche_ATR(A->droit, mot);
    }
    else {
        return 0;
    }
}


int supprimer (ATR* A, char* mot) {
    ATR temp;
    /* si A est vide on renvoie 0 */
    if ((*A) == NULL) {
        return 0;
    }
    /* si la première lettre du mot est la lettre de l'arbre*/
    if ((*A)->lettre == *mot) {
        /* on verifie qu'on est a la derniere lettre du mot */
        if (*mot == '\0') {
            /* si c'est le cas on supprime la lettre et on fait remonter son frère droit */
            temp =(*A);
            *A = (*A)->droit;
            free(temp);
            return 1;
        }
        /* sinon on continue a parcourir le mot */
        supprimer_dans_ATR(&(*A)->fils, mot + 1);
        if((*A)->droit == NULL && (*A)->gauche == NULL && (*A)->fils == NULL) {
            free(*A);
            *A = NULL;
        }
        return 0;
    }
    /* si la première lettre est superieure que la lettre de la racine on lance la fonction sur le sous arbre droit */
    if ((*A)->lettre < *mot ) {
        return supprimer(&(*A)->droit, mot);
    }
    /* si la première lettre est inférieure que la lettre de la racine on lance la fonction sur le sous arbre gauche */
    else if ((*A)->lettre > *mot ) {
        return supprimer(&(*A)->gauche, mot);
    }
    return 0;
}

void supprimer_dans_ATR(ATR* A, char* mot) {
    supprimer(&(*A), mot);
}
