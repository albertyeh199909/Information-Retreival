 #include <stdio.h>
#include "invertedIndex.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  
void printLL (TfIdfList L) ;
int main(int arg, char *argv[]) {

        //printf("Normalised : %s\n", normaliseWord(argv[1]));
        //printInvertedIndex(generateInvertedIndex(argv[1]));
        char arr[] = {'m','o','o','n','\0'};
        printLL(calculateTfIdf(generateInvertedIndex(argv[1]), arr , 20));
        return 0 ;
}

void printLL (TfIdfList L) {
        TfIdfList curr = L;
        if (L == NULL) {
                return;
        }
        if (L->next == NULL) {
                printf("%lf ", L->tfidf_sum);
                
        }
        else {
                while (curr->next != NULL) {
                        printf("%lf ", L->tfidf_sum);
                        curr = curr->next;
                }
        }
}        
