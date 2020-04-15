#include <stdio.h>
#include "invertedIndex.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  




static InvertedIndexBST insertTree (InvertedIndexBST t,  char *word, char* fileName);
static InvertedIndexBST newNode (char *word, char* fileName);
static void updateLL (InvertedIndexBST t, char* fileName);
static FileList newLLNode (char *fileName);
static int countFileWord (char *fileName);
static void tfDivide (InvertedIndexBST t);
static void helperPrint(InvertedIndexBST tree, FILE* fp);
//first word doesnt exist in tree
//      - Create node
//      - insert in the right place
//      - add filename to linked list
//second word does exist
//      - find the existing node
//      - update filename linked list, adding this filename (be careful not to add the same file twice)
//      infix


char *normaliseWord(char *str) {
        int j = strlen(str) - 1;
        while (str[j] == ' ') {
                str[j] = '\0';
                j--;
        }
        int i = 0;
        while (str[i] != '\0') {
        //remove spaces by shifting counting from str[0]
        //strlnth - 1 until != ' ' 
                if (i == 0) {
                        int z = 0;
                        while (str[z] == ' ') {
                                int y = 0;
                                while (str[y] != '\0') {
                                        str[y] = str[y+1];
                                        y++;
                                }
                                
                        }
                }           
                str[i] = tolower(str[i]);
                if (str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '.') {
                        if (str[i + 1] == '\0') {
                                str[i] = '\0';
                        }
                }
                i++;
        }
      
        return str;
}    
        
InvertedIndexBST generateInvertedIndex (char *collectionFilename) {
    char *fileName = malloc(sizeof(char)*100);
    FILE *collection = fopen(collectionFilename, "r");
    InvertedIndexBST tree = NULL;
    //read collection.txt and each file
    while (fscanf(collection, "%s", fileName) == 1) {
        FILE *currFile = fopen(fileName, "r"); 
        char *word = malloc(sizeof(char)*100);
        //read each word  
        while (fscanf(currFile, "%s", word) == 1) {
            //call newNode function
            //call insert function
            word = normaliseWord(word);
            tree = insertTree(tree, word, fileName);
        }
    }
    tfDivide (tree); 
    
    return tree;           
}
// creates new node for binary tree
static InvertedIndexBST newNode (char *word, char* fileName) {
        InvertedIndexBST BSTnode = malloc (sizeof(InvertedIndexBST));
        int x = strlen(word) + 1;
        //x = x + 1;
        char *copy = malloc(sizeof(char)*x);
        char *nodeWord = strcpy(copy, word);
        //malloc array sizeof(char*strlen(word) + 1) and strcpy
        BSTnode->word = nodeWord;
        BSTnode->fileList = newLLNode(fileName);
        BSTnode->left = NULL;
        BSTnode->right = NULL;
        return BSTnode;
}
// insert nodes into tree        taken from week03 lab        
static InvertedIndexBST insertTree (InvertedIndexBST t,  char *word, char* fileName) {
        if (t == NULL) {
                return (newNode(word, fileName));
        }
        else if (strcmp(t->word, word) > 0) {
                t->left = insertTree(t->left, word, fileName);
        }
        else if (strcmp(t->word, word) < 0) {
                t->right = insertTree(t->right, word, fileName); 
        }
        else if (strcmp(t->word, word) == 0) {
                updateLL(t, fileName);
        }
        return t;
} 

static void helperPrint(InvertedIndexBST tree, FILE* fp) {
        if (tree == NULL) {
                return;
        }
        helperPrint (tree->left, fp);
        // Print info of root node
        fprintf (fp, "%s ", tree->word);
        fflush(fp);
        FileList curr = tree->fileList;
        if (curr->next == NULL) {
                fprintf(fp, "%s ", curr->filename);
                fflush(fp);
        }        
        else {
                while (curr->next != NULL) {
                        fprintf(fp, "%s ", curr->filename);
                        curr = curr->next;
                }
        }
        fprintf(fp, "\n");
        fflush(fp);
        helperPrint (tree->right, fp);
}
void printInvertedIndex(InvertedIndexBST tree) {   
        FILE* fp = fopen ("invertedIndex.txt", "w+");  
        helperPrint(tree, fp);
        fclose(fp);
        



}  
//inserts node into link list or updates tf
static void updateLL (InvertedIndexBST t, char* fileName)  {
        FileList curr = t->fileList;
        if (curr == NULL) {
                curr = newLLNode(fileName);
                t->fileList = curr;
                curr->next = NULL;
        }
        else if (strcmp(t->fileList->filename, fileName) > 0) {
                FileList tmp = t->fileList;
                t->fileList = newLLNode(fileName);
                t->fileList->next = tmp;
        }
        else if (strcmp(t->fileList->filename, fileName) > 0) {
                t->fileList->tf = t->fileList->tf + 1;        
        }
        else {                       
                while (curr->next != NULL) {
                        if (curr->next != NULL) {
                                if (strcmp(curr->next->filename, fileName) > 0) {
                                             
                                        FileList tmp = curr->next;
                                        curr->next = newLLNode(fileName);
                                        curr->next->next = tmp;
                                }        
                                if (strcmp(curr->filename, fileName) == 0) {
                                        break;
                                        t->fileList->tf = t->fileList->tf + 1;     
                                        //insert in order
                                        //change tf
                                        // increment 1, divide in print
                                        //how to get total words of file??
                                }
                        }
                        curr = curr->next;
                }
                if (strcmp(curr->filename, fileName) < 0) {                   
                        curr->next = newLLNode(fileName);
                        curr->next->next = NULL;
                }        
                if (strcmp(curr->filename, fileName) == 0) {
                        t->fileList->tf = t->fileList->tf + 1;     
                        //insert in order
                        //change tf
                        //how to get total words of file??
                }
        }

}
//creates new node for linked list
static FileList newLLNode (char *fileName) {
         FileList LLnode = malloc (sizeof(FileList));
         int x = strlen(fileName) + 1;
         char *copy = malloc(sizeof(char)*x);
         char *nodeFileName = strcpy(copy, fileName);
         LLnode->filename = nodeFileName;
         LLnode->tf = 1;
         LLnode->next = NULL;
         return LLnode;
}

static int countFileWord (char *fileName) {
        int wordCount = 0;
        FILE *currFile = fopen(fileName, "r");
        char buffer[100];
        while (fscanf(currFile, "%s", buffer) == 1) {
                wordCount ++;
        }
        return wordCount;
}
//divides word count in each node of total word in list
static void tfDivide (InvertedIndexBST t) {
        if (t == NULL) {
                return;
        }
        if (t->fileList != NULL) {
                t->fileList->tf = t->fileList->tf/countFileWord(t->fileList->filename);
        }
        tfDivide(t->left);
        tfDivide(t->right);
}
        
        
/*
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {
        InvertedIndexBST t = binarySearch(tree, searchWord);
        TfidfList tfidfLL = NULL;
        if (t != NULL) {
                FileList curr = t->fileList;
                while (curr->next != NULL) {
                        double tfidf = calculate (curr->tf,    ,D);
                                                              


}    

static InvertedIndexBST binarySearch (InvertedIndexBST t,  char *word) {
        if (t == NULL) {
                ;return NULL
        else if (strcmp(t->word, word) > 0) {
                return binarySearch(t->left, word, fileName);
        }
        else if (strcmp(t->word, word) < 0) {
                return binarySearch(t->right, word, fileName); 
        }
        else if (strcmp(t->word, word) == 0) {
                return t;
        }
        return t;
} 

double calculate (double tf, int wordFile, int D) {
        double x = D/(double)wordFile;
        double tfidf = tf * log(x);
} 

TfidfList createTfidfNode (double tfidf, char *fileName) {
        TfidfList node = malloc(sizeof(TfidfList));
        node->tfidf_sum = tfidf;
        int x = strlen(fileName) + 1;
        char *copy = malloc(sizeof(char)*x);
        char *nodeWord = strcpy(copy, fileName);
        node->fileName = nodeWord;
        node->next = NULL;
}
*/                        

