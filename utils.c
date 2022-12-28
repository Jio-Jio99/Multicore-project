#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


// LETTURA DI FILE, RITORNA UN TESTO COME UN UNICA STRINGA
char* ReadFile(char *filename){
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

    if (handler){
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size){
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
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


// ALGORITMO di Knuth-Morris-Pratt
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
char** StrSplit(char* a_str, const char a_delim) {
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
