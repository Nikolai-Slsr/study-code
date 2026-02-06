#include <stdio.h>

int myNumbers[5] = {10,20,30,40,50};

int main(){
    int* firstPointer = &myNumbers[0];
    int* secondPointer = &myNumbers[4];
    printf("P1: %p, P2 %p, Difference: %ld \n", firstPointer, secondPointer, -firstPointer-secondPointer);
    return(0);
}