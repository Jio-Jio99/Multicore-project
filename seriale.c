#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.c"

void serialeFunction(char *testo, char** pattern);

// Main per il processo seriale
int main(int argc, char* args[]) {
    //Controllo che i parametri passati siano del numero esatto, il IV è il numero di processi paralleli da avviare
    if (argc != 3) {
        printf("Error: errore nei parametri passati\n");
        return 0;
    } 

    //Prendo i nomi dei file
    char* filenameTxt = args[1];
    char* filenamePatt = args[2];

    // Leggo i file e metto in memoria, controllando che non ci siano errori
    //File del testo da controllare
    char* txt = ReadFile(filenameTxt);
    if (txt == NULL){
        printf("Error: file of TEXT not exist");
        return 0;
    }

    //File dei pattern da cercare
    char* pat = ReadFile(filenamePatt);
    if (pat == NULL){
        printf("Error: file of PAT not exist");
        return 0;
    }

    // Del file path splitto sugli '\n' per poter successivamente ciclare sulle stringhe da verificare
    char** listaPat = StrSplit(pat, '\n', NULL);

    // Funzionamento del processo seriale, per ogni pattern avvio la funzione di ricerca
    //Calcolo dei tempi
    clock_t start, end;
    start = clock();
    //Funzione seriale
    serialeFunction(txt, listaPat);
    end = clock();
    printf("\nTime: %f\n", ((double)(end - start))/CLOCKS_PER_SEC);
    return 0;
}

void serialeFunction(char *testo, char** pattern){
    int volte;
    //Ciclo su tutti i pattern dati finchè l'array non è vuoto
    for(int i=0; *(pattern + i); i++){
        volte = 0;
        printf("Trovata la parola \"%s\"", *(pattern+i));
        KMPSearchInt(pattern[i], testo, &volte); //Algoritmo che calcola le ricorrenze della parola data
        printf(" %d volte\n", volte);
    }

    return;
}