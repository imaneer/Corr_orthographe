/*
 * Auteurs : Sarah ENG, Imane ERRAHMANI
 * Creation : 26-03-2022
 * Modification : 26-03-2022
 */
#include "Levenshtein.h"



/* Fonction qui recoit trois entiers et renvoie le maximum des trois.
 */
int min(int a, int b, int c){	
	if(a <= b && a <= c){
		return a;
	}
	else if(b <= a && b <= c){
		return b;
	}
	return c;
}


/* Fonction qui recoit deux chaines de caracteres et renvoie leur distance de Levenshtein.
 */
int Levenshtein(char *un, char *deux) {
    int **D;
    int i, j, coutSubstitution;
    D = (int**)malloc(sizeof(int*)*strlen(un)+1);
    if (!D) exit(EXIT_FAILURE);
    for (i = 0; i <= strlen(un); i++) {
        D[i] = (int*)malloc(sizeof(int)*strlen(deux)+1);
        if (!D[i]) exit(EXIT_FAILURE);
        for (j = 0; j <= strlen(deux); j++) {
            D[i][j] = 0;
        }
    }
    for (i = 0; i <= strlen(un); i++ ) {
        D[i][0] = i;
    }
    for (j = 0; j <= strlen(deux); j++ ) {
        D[0][j] = j;
    }
    for (i = 1; i <= strlen(un); i++ ) {
        for (j = 1; j <= strlen(deux); j++ ) {
            if (un[i-1] == deux[j-1]) {
                coutSubstitution = 0;
            }
            else {
                coutSubstitution = 1;
            }
            D[i][j] = min(D[i-1][j] + 1, D[i][j-1] + 1, D[i-1][j - 1] + coutSubstitution);
        }
    }
    return D[strlen(un)][strlen(deux)];
}
