#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.c"

// Driver program to test above function
int main(int argc, char* args[]) {
    char* txt = ReadFile("gioele.txt");
    if (txt == NULL){
        printf("Errore nella lettura del file");
        return 0;
    }

    char* pat = "Dix";

    KMPSearch(pat, txt);
    return 0;
}