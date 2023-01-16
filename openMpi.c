#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "utils.c"

int main(int argc, char* args[]){
    if (argc != 4) {
        printf("Error: mancano dei parametri\n");
        return 0;
    } 

    char* filenameTxt = args[1];
    char* filenamePath = args[2];
    int thread_count = atoi(args[3]);

    if (thread_count == 0){
        printf("Error: input tread count with a integer");
        return 0;
    }

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
    int numberPat = 0;
    char** listaPat = StrSplit(pat, '\n', &numberPat);

    // Idea: ciclare sui pattern e ad ogni pattern mandare un thread
    double start, end;
    start = omp_get_wtime();
    #pragma  omp  parallel num_threads(thread_count)
    {
        int volte = 0; 
        #pragma omp for private(volte) 
            for (int i = 0; i < numberPat; i++){
                if (!listaPat[i]){
                    continue;
                }
                volte = 0; 
                KMPSearchInt(listaPat[i], txt, &volte);
                // KMPSearch(listaPat[i], txt);
                printf("Ricercato \"%s\" dal processo %d di %d: %d ricorenze trovate\n", listaPat[i], omp_get_thread_num(),omp_get_num_threads(),volte);
            }
    }
    end = omp_get_wtime();
    printf("\nTime: %f\n", end - start);
    return 0;
}

//Fare più txt copie profonda (anche della lista de)