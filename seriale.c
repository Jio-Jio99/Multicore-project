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
    int numberPat;
    char** listaPat = StrSplit(pat, &numberPat);

    // Funzionamento del processo seriale, per ogni pattern avvio la funzione di ricerca iterativamente
    
    //Calcolo dei tempi
    clock_t start, end;
    start = clock();
    
    //Funzione seriale
    int volte;

    //Ciclo su tutti i pattern dati
    for(int i=0; i < numberPat; i++){
        volte = 0;
        //Algoritmo di ricerca
        KMPSearchInt(listaPat[i], txt, &volte); //Algoritmo che calcola le ricorrenze della parola data
        printf("Trovata la parola \"%s\" %d volte\n", listaPat[i], volte);
    }
    
    //Tempo impiegato
    end = clock();
    printf("\nTime: %f\n", ((double)(end - start))/CLOCKS_PER_SEC);
    return 0;
}