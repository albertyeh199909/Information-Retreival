
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char *normaliseWord(char *str);

int main(void) {
        

        char arr[] = {' ',' ',' ',' ','C','O','D','D','?','?',' ',' ','\0'};

        char *new = normaliseWord(arr);
        printf("%s"  ,new);







}









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
