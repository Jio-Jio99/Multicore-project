#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void computeLPSArray(char *pat, int lungPattern, int *longestPrefixSuffix);
void KMPSearch(char *pat, char *txt);

// Driver program to test above function
int main() {
    char *txt = "ABABDABACDABABCABAB";
    char *pat = "ABABCABAB";
    KMPSearch(pat, txt);
    return 0;
}

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

        // mismatch after j matches
        else if (i < lungText && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = longestPrefixSuffix[j - 1];
            else
                i = i + 1;
        }
    }

    free(longestPrefixSuffix); // to avoid memory leak
}

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