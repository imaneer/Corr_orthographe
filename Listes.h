/*
 * Auteurs : Imane ERRAHMANI, Sarah ENG
 * Creation : 08-03-2022
 * Modification : 19-03-2022
 */
#ifndef __Listes__
#define __Listes__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule {
    char *mot;
    struct cellule *suivant;
} Cellule, *Liste;

/* Fonction qui alloue une cellule, et si l'allocation a reussi elle renvoie son adresse, sinon NULL.
 * S'il n'y a aucun probleme d'allocation, elle initialise le champ mot par la chaine de caractere reçue
 * en parametre, et le champ suivant par NULL.
 */
Cellule* allouer_Cellule(char *mot);

/* Fonction qui insere en tete de la liste L la chaine de caracteres mot.
 * Elle renvoie 1 si l'insertion a ete effectuee, et 0 s'il y a eu un probleme.
 */
int inserer_en_tete(Liste *L, char *mot);

/* Fonction qui renvoie 1 si le mot est deja present dans la liste, et 0 sinon.
 */
int appartient(Liste L, char *mot);

/* Fonction qui libere l'espace memoire dedie à tous les elements de la liste.
 */
void liberer_Liste(Liste* L);

/* Fonction qui affiche, un par ligne, tous les elements de la liste.
 */
void afficher_Liste(Liste L);

#endif