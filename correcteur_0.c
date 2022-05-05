/*
 * Auteurs : Imane ERRAHMANI, Sarah ENG
 * Creation : 08-03-2022
 * Modification : 20-03-2022
 */
#include "ATR.h"
#include "Listes.h"

/* Fonction qui ouvre un fichier en mode lecture.
 * Elle renvoie ce fichier s'il a pu etre ouvert,
 * sinon, elle affiche un message dans la sortie d'erreur et quitte le programme sinon.
 */
FILE *ouvre_fichier(const char *chemin) {
    FILE *df = fopen(chemin, "r");
    if (df == NULL) {
        fprintf(stderr, "impossible d'ouvrir %s", chemin);
        exit(1);
    }
    return df;
}
/* Fonction qui verifie si le nombre d'argument est bien 2 
 * (le dictionnaire et le texte à corriger)
 */
void verifie_appel(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage : %s <fichier à lire>", argv[0]);
        exit(0);
    }
}

/* Fonction qui convertit les majuscules en minuscules dans le tableau de caracteres mot.
 */
void Maj_to_Min (char *mot) {
    int i;
    i = 0;
    /* Parcours du mot, et conversion d'une majuscule en minuscule si besoin */
    while (mot[i] != '\0') {
        if ('A' <= mot[i] && mot[i] <= 'Z'){
            mot[i] = mot[i] - 'A' + 'a';
        }
        i += 1;
    }
}

int main (int argc, char* argv[]) {
    /* Creation de l'ATR qui contiendra les mots du dictionnaire */
    ATR A = creer_ATR_vide();
    /* Creation de la liste chainee qui contiendra les mots qui sont mal orthographies selon le dico */
    Liste erreurs = NULL;
    /* Ouverture du fichier qui contient les mots à corriger */
    FILE *a_corriger = ouvre_fichier(argv[1]);
    /* Ouverture du fichier qui contient les mots du dico */
    FILE *dico = ouvre_fichier(argv[2]);
    char mot[TAILLE_MOT];
    char m[TAILLE_MOT];
    /* Remplissage de l'ATR avec les mots du dico */
    while ((fscanf(dico, "%s", mot)) != EOF) {
        inserer_dans_ATR(&A, mot);
    }
    fclose(dico);
    /* Affichage des mots de l'ATR */
    printf("selon ce dictionnaire\n");
    afficher_ATR(A);
    /* Lecture mot à mot du fichier à corriger */
    while((fscanf(a_corriger, "%s ", m)) == 1) {
        /* Conversion des majuscules en minuscules si besoin */
        Maj_to_Min(m);
        /* Si le mot n'existe pas dans le dico, on l'ajoute dans la liste des erreurs */
        if((recherche_ATR(A, m) == 0) ){
            inserer_en_tete(&erreurs, m);
        }
    }
    /* Affichage des mots mal orthographies selon le dico */
    printf("-------------------------\n");
    printf("les mots mal orthographies sont :\n");
    afficher_Liste(erreurs);
    fclose(a_corriger);
    return 0;
}