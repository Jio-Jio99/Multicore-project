#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "utils.c"

int main(int argc, char* args[]){
    //Inizializzazione e pars dei parametri
    //Controllo che i parametri passati siano del numero esatto, il IV è il numero di processi paralleli da avviare
    if (argc != 6) {
        printf("Error: mancano dei parametri\n");
        return 0;
    } 

    //Prendo i nomi dei file (sono gli ultimi inseriti)
    char* filenameTxt = args[4];
    char* filenamePatt = args[5];
    //Prendo il numero di processi
    int comm_sz = atoi(args[3]);

    //Controllo che non ci siano stati errori nella conversione
    if (comm_sz == 0){
        printf("Error: input tread count with a integer");
        return 0;
    }

    // Leggo i file e alloco una parte di memoria dedicata, controllando che non ci siano errori
    //File TESTO
    char* txt = ReadFile(filenameTxt);
    if (txt == NULL){
        printf("Error: file of TEXT not exist");
        return 0;
    }

    //File dei pattern
    char* pat = ReadFile(filenamePatt);
    if (pat == NULL){
        printf("Error: file of PAT not exist");
        return 0;
    }

    //Del file patt splitto sugli '\n' per poter successivamente ciclare sulle stringhe da verificare
    int numberPat = 0; //Mi salvo quanti pattern ha trovato nel file così da poter avere una costante nel for
    char** listaPat = StrSplit(pat, '\n', &numberPat);

    //Inizio programma con MPI
    //Creazione dei processi
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    
    //Idea: suddividere la lista di pattern in parti uguali da dividere ai vari processi 
    //Misurazione per il tempo
    double start, end;
    start = MPI_Wtime();
    
    // FUNZIONE CON MPI
    
    end = MPI_Wtime();
    //stampa finale del tempo messo
    MPI_Finalize();
    printf("\nTime: %f\n", end - start);
    return 0;
}