#include <stdio.h>

char string[30] = "Curly bird catches the worm";

char *pString = string;
void changeSecondC(char * string){
    *(string + 1) = 'c';
}
int main(){
    changeSecondC(pString);
    printf("%s",pString);
    return(0);
}