#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.c"

void serialeFunction(char *testo, char** pattern);

// Main per il processo seriale
int main(int argc, char* args[]) {
    if (argc != 3) {
        printf("Error: errore nei parametri passati\n");
        return 0;
    } 

    char* filenameTxt = args[1];
    char* filenamePath = args[2];

    // Leggo i file e metto in memoria, controllando che non ci siano errori
    char* txt = ReadFile(filenameTxt);
    if (txt == NULL){
        printf("Error: file of TEXT not exist");
        return 0;
    }

    char* pat = ReadFile(filenamePath);
    if (pat == NULL){
        printf("Error: file of PAT not exist");
        return 0;
    }

    // Del file path splitto sugli '\n' per poter successivamente ciclare sulle stringhe da verificare
    char** listaPat = StrSplit(pat, '\n', NULL);

    // Funzionamento del processo seriale, per ogni token avvio la funzione
    clock_t start, end;
    start = clock();
    serialeFunction(txt, listaPat);
    end = clock();
    printf("\nTime: %f\n", ((double)(end - start))/CLOCKS_PER_SEC);
    return 0;
}

void serialeFunction(char *testo, char** pattern){
    int volte;
    for(int i=0; *(pattern + i); i++){
        volte = 0;
        printf("Trovata la parola \"%s\"", *(pattern+i));
        KMPSearchInt(pattern[i], testo, &volte);
        // KMPSearch(pattern[i], testo);
        printf(" %d volte\n", volte);
    }

    return;
}