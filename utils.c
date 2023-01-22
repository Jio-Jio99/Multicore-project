#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// LETTURA DI FILE, RITORNA UN TESTO COME UN UNICA STRINGA
char* ReadFile(char *filename){
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

    if (handler){
        // Spostiamo il puntatore alla fine del file
        fseek(handler, 0, SEEK_END);
        // Misurazione di quanti byte è composto il file
        string_size = ftell(handler);
        // ripuntiamo all'inizio del file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        // Legge tutto il file in un'unica operazione
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // aggiunta del \0 finale che fread non inserisce
        buffer[string_size] = '\0';

        if (string_size != read_size){
            // in caso di errori di memoria, liberiamo la stessa e mandiamo il puntatore a NULL
            free(buffer);
            buffer = NULL;
        }

        // Chiusura file
        fclose(handler);
    }

    return buffer;
}

// FUNZIONE DI SUPPORTO PER L'ALGORITMO DI CONFRONTO
void computeLPSArray(char *pat, int lungPattern, int *longestPrefixSuffix) {
    int lpsLen = 0; // lenght of the previous longest prefix suffix
    int i;

    longestPrefixSuffix[0] = 0; // lps[0] is always 0
    i = 1;

    // the loop calculates longestPrefixSuffix[i] for i = 1 to lungPattern-1
    while (i < lungPattern) {
        if (pat[i] == pat[lpsLen]) { 
            lpsLen++;
            longestPrefixSuffix[i] = lpsLen;
            i++;
        }
        else { // (pat[i] != pat[lpsLen])
            if (lpsLen != 0) {
                // This is tricky. Consider the example AAACAAAA and i = 7.
                lpsLen = longestPrefixSuffix[lpsLen - 1];
                // Also, note that we do not increment i here
            } else { // if (lpsLen == 0)
                longestPrefixSuffix[i] = 0;
                i++;
            }
        }
    }
}


// ALGORITMO di Knuth-Morris-Pratt che stampa il puntatore di dove trova la parola
void KMPSearch(char *pat, char *txt) {
    int lungPattern = strlen(pat);
    int lungText = strlen(txt);

    // create lps[] that will hold the longest prefix suffix values for pattern
    int *longestPrefixSuffix = (int *) malloc(sizeof(int) * lungPattern);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, lungPattern, longestPrefixSuffix);

    int j = 0; // index for pat[]
    int i = 0; // index for txt[]
    while (i < lungText) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == lungPattern) {
            printf("Found pattern at index %d \n", i - j);
            j = longestPrefixSuffix[j - 1];
        }
        else if (i < lungText && pat[j] != txt[i]) { // mismatch after j matches
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = longestPrefixSuffix[j - 1];
            else
                i++;
        }
    }

    free(longestPrefixSuffix); // to avoid memory leak
}

// SPLITTA UN TESTO PER GLI SPAZI E RITORNA UN ARRAY DI STRINGHE
char** StrSplit(char* string, int* numberPat) {
    int countPatt = 0;
    // array di stringhe da ritornare
    char ** splittata = (char**) malloc(sizeof(char*));
    if (!splittata){
        printf("Errore: mancanza di memoria per splittare la stringa");
        exit(0);
    }

    // Estraggo il primo pattern
    char * token = strtok(string, "\n");
    if(!token){
        printf("Errore, non trovato nessun pattern");
        exit(0);
    }

    splittata[0] = (char *) malloc(strlen(token)*sizeof(char));
    strcpy(splittata[0], token);
    countPatt = 1;

    // loop fino all'ultimo token
    while( token != NULL ) {
        token = strtok(NULL, "\n");
        if(token != NULL){
            splittata = realloc(splittata, (countPatt+1)*sizeof(char*));
            if(!splittata){
                printf("Errore: spazio di memoria insufficiente per i pattern");
                exit(0);
            }
            splittata[countPatt] = (char *) malloc(strlen(token)*sizeof(char));
            if(!splittata[countPatt-1]){
                printf("Errore: spazio di memoria insufficiente per i pattern");
                exit(0);
            }
            strcpy(splittata[countPatt], token);
            countPatt++;
        }
    }

    *(numberPat) = countPatt;
    return splittata;
}

// ALGORITMO di Knuth-Morris-Pratt che invece di stampare l'indice della posizione ritorna quante volte ha trovato quel pattern
void KMPSearchInt(char *pat, char *txt, int* n_volte) {
    int lungPattern = strlen(pat);
    int lungText = strlen(txt);

    // create lps[] that will hold the longest prefix suffix values for pattern
    int *longestPrefixSuffix = (int *) malloc(sizeof(int) * lungPattern);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, lungPattern, longestPrefixSuffix);

    int j = 0; // index for pat[]
    int i = 0; // index for txt[]
    while (i < lungText) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == lungPattern) {
            *(n_volte)+=1;
            j = longestPrefixSuffix[j - 1];
        }
        else if (i < lungText && pat[j] != txt[i]) { // mismatch after j matches
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = longestPrefixSuffix[j - 1];
            else
                i++;
        }
    }

    free(longestPrefixSuffix); // to avoid memory leak
}