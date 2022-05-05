/*
 * Auteurs : Sarah ENG, Imane ERRAHMANI
 * Creation : 26-03-2022
 * Modification : 26-03-2022
 */
#include "ATR.h"
#include "Listes.h"
#include "Levenshtein.h"

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

/* Fonction qui affiche le mot a corriger et les propositions de correction selon le dico
 */
void affiche_correction(char *mot, Liste correction) {
    /* Affichage du mot mal orthographie */
    printf("Mot mal orthographie : %s\n", mot);
    /* Affichage de la premiere proposition de correction */
    printf("Proposition(s) : %s", correction->mot);
    /* Parcours de la liste de correction et affichage de ces propositions de correction */
    correction = correction->suivant;
    while (correction != NULL) {
        printf(", %s", correction->mot);
        correction = correction->suivant;
    }
    printf("\n");
}

int main (int argc, char* argv[]) {
    /* Creation de l'ATR qui contiendra les mots du dictionnaire */
    ATR A = creer_ATR_vide();
    /* Creation de la liste chainee qui contiendra les mots qui sont mal orthographies selon le dico */
    Liste erreurs = NULL;
    /* Creation de la liste chainee qui permettra le parcours de la liste des erreurs */
    Liste tmp = NULL;
    /* Creation de la liste chainee qui contiendra les propositions de correction des mots qui sont mal orthographies selon le dico */
    Liste correction;
    /* Variable qui contiendront les distances de Levenshtein */
    long d_min, d;
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
    
    printf("------------Mot mal orthographie-------------\n");
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
    afficher_Liste(erreurs);
    fclose(a_corriger);
    printf("-------------------------\n");
    
    tmp = erreurs;
    /* Parcours de la liste des erreurs */
    while(tmp != NULL) {
        /* Curseur au debut du fichier du dico */
        rewind(dico);
        /* Initialisation de d_min avec un nombre grand, et de la liste chainee de corrections */
        d_min = 276447231;
        correction = NULL;
        /* Lecture mot à mot du fichier du dico */
        while ((fscanf(dico, "%s", mot)) != EOF) {
            /* Calcul de la distance de Levenshtein du mot lu (dico) et du mot a corriger */
            d = Levenshtein(mot, tmp->mot);
            /* Si cette distance est inferieure a la distance minimale trouvee precedemment */
            if (d <= d_min) {
                /* Si cette distance est strictement inferieure a la distance minimale trouvee precedemment */
                if (d < d_min) {
                    /* Acutalisation de la distance minimale */
                    d_min = d;
                    /* Vide la liste correction */
                    liberer_Liste(&correction);
                    correction = NULL;
                }
                /* Insertion du mot lu dans la liste de corrections */
                inserer_en_tete(&correction, mot);
            }
        }
        /* Lorsqu'on a fini de lire le fichier du dico, on affiche les corrections */
        affiche_correction(tmp->mot, correction);
        /* On passe au mot a corriger suivant */
        tmp = tmp->suivant;
    }
    
    fclose(dico);
    return 0;
}