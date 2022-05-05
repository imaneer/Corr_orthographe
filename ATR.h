/*
 * Auteurs : Imane ERRAHMANI, Sarah ENG
 * Creation : 08-03-2022
 * Modification : 19-03-2022
 */
#ifndef __ATR__
#define __ATR__
#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MOT 50

typedef struct noeud {
    char lettre;
    struct noeud *gauche, *fils, *droit;
} Noeud, *ATR;

/* Fonction qui cree et renvoie un ATR vide.
 */
ATR creer_ATR_vide();

/* Fonction qui libere l'espace memoire dedie Ã  tous les elements de l'ATR.
 */
void liberer_ATR(ATR *A);

/* Fonction qui renvoie 1 si l'ajout du mot dans l'ATR a reussi, et 0 sinon.
 */
int inserer_dans_ATR(ATR *A, char *mot);
/* Fonction qui supprime un mot d'un ATR.
 */
void supprimer_dans_ATR(ATR *A, char *mot);

/* Fonction qui affiche les mots de l'ATR.
 */
void afficher_ATR(ATR A);

/* Fonction qui renvoie 1 si le mot est dans l'ATR, et 0 sinon.
 */
int recherche_ATR (ATR A, char *mot);

#endif