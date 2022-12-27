#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.c"

// Main per il processo seriale
int main(int argc, char* args[]) {
    char* filenameTxt = "gioele.txt";
    char* filenamePath = "gioele.txt";

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
    char** listaPat = StrSplit(pat, '\n');

    // Funzionamento del processo seriale, per ogni token avvio la funzione
    for(int i=0; *(listaPat + i); i++){
        KMPSearch(listaPat[i], txt);
    }
    return 0;
}