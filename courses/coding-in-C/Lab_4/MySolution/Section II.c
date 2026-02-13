#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkForPalindrome(char * word){
    short length = strcspn(word, "\n");
    char * leftPointer = word;
    char * rightPointer = word + (length - 1);

    while(rightPointer >= leftPointer){
        if (*leftPointer != *rightPointer){return(0);}
        rightPointer --;
        leftPointer ++;
    }
    return(1);
}
int main(){
    char input[100];
    printf("Word(s) to check: \n");
    // Ursprünglich hab ich die Überprüfung von der Eingabe vergessen
    // alt: fgets(input, sizeof(input), stdin);

    // neu:
    if(fgets(input, sizeof(input), stdin)){
        printf("Error while reading Input \n");
        return(1);
    }

    short isPalindrome = checkForPalindrome(input);
    input[strcspn(input, "\n")] = 0;

    if (isPalindrome)
    {
        printf("Your provided word %s is a palindrome. \n",input);
        return(0);
    }
    printf("Your provided word %s is not a palindrome. \n",input);
        return(0);
}

