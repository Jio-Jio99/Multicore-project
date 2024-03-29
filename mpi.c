#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "utils.c"

int main(int argc, char* args[]){
    //Inizializzazione e pars dei parametri
    //Controllo che i parametri passati siano del numero esatto, il IV è il numero di processi paralleli da avviare
    if (argc != 3) {
        printf("Error: mancano dei parametri\n");
        return 0;
    } 

    //Prendo i nomi dei file (sono gli ultimi inseriti)
    char* filenameTxt = args[1];
    char* filenamePatt = args[2];


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
    char** listaPat = StrSplit(pat, &numberPat);

    //Inizio programma con MPI

    //Creazione dei processi
    MPI_Init(NULL, NULL);

    //Prendo il tempo iniziale per ogni processo
    double start = MPI_Wtime();

    //Variabili private
    int my_rank, comm_sz, volte;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //Misurazione per il tempo
    double end;

    //Idea: suddividere i vari pattern da dare ai processi a seconda del my_rank del processo finché i pattern non sono finiti 
    for(int i = 0; i < numberPat; i += comm_sz){
        volte=0;
        //Controllo in caso la lista non sia divisibile per i processi avviati, per evitare che si vada fuori array
        if(i+my_rank>=numberPat || !listaPat[i+my_rank]){
            break;
        }
        KMPSearchInt(listaPat[i+my_rank], txt, &volte);
        printf("Ricercato \"%s\" dal processo %d di %d: %d ricorrenze trovate\n", listaPat[i+my_rank], my_rank+1, comm_sz, volte);
    }
    //Tempo finale
    end = MPI_Wtime();

    //tempo messo dal processo
    double my_time = end-start, maximumTime=0;
    
    //Prendo il tempo del processo più lento
    MPI_Reduce(&my_time, &maximumTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    
    if (my_rank==0){
        printf("\nTime: %f\n", maximumTime);
    }
    MPI_Finalize();

    return 0;
}