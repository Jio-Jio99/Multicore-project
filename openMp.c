#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "utils.c"

int main(int argc, char* args[]){
    //Inizializzazione e pars dei parametri
    //Controllo che i parametri passati siano del numero esatto, il IV è il numero di processi paralleli da avviare
    if (argc != 4) {
        printf("Error: mancano dei parametri\n");
        return 0;
    } 

    //Prendo i nomi dei file
    char* filenameTxt = args[1];
    char* filenamePatt = args[2];
    //Prendo il numero di processi
    int thread_count = atoi(args[3]);

    //Controllo che non ci siano stati errori nella conversione
    if (thread_count == 0){
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
    char** listaPat = StrSplit(pat, &numberPat);

    // Idea: ciclare sui pattern mandando in parallelo il for, quindi suddividere i pattern da cercare tra i vari processi
    //Misurazione per il tempo
    double start, end;
    start = omp_get_wtime();
    #pragma  omp  parallel num_threads(thread_count)
    {
        int volte = 0;  //Variabile privata dei vari thread che serve per calcolare quante volte è stata trovata la parola
        #pragma omp for private(volte) 
            //For dei pattern che va da 0 a numberPat -1 
            for (int i = 0; i < numberPat; i++){
                if (!listaPat[i]){
                    continue;//Controllo in più per verificare se non si va in una parte di memoria vuota, altrimenti continua con il ciclo per poi uscire
                }
                volte = 0; 
                KMPSearchInt(listaPat[i], txt, &volte); //Algoritmo che cerca le ricorrenze nei testi
                printf("Ricercato \"%s\" dal processo %d di %d: %d ricorenze trovate\n", listaPat[i], omp_get_thread_num(),omp_get_num_threads(),volte);
            }
    }
    end = omp_get_wtime();
    
    //stampa finale del tempo messo
    printf("\nTime: %f\n", end - start);
    return 0;
}