#include <stdio.h>

void printCollumLabels(int size)
    {
        char initLetter = 65;
        printf("    ");
        for (char collum = initLetter; collum < size + initLetter; collum++)
        {
            printf("%-4c",collum);
        }
        printf("\n");
    }
    void printBorder(short size){
        printf("  +");
        for (short i = 0; i < size; i++)
        {
            printf("---+");
        }
        printf("\n");

    }
    void printRow(short size, short row){
        printf("%d |", row);
        for (short i = 1; i < size + 1; i++)
        {
            if ((row + i)%2 == 0)
            {
                printf("###|");
            }
            else{
                printf("   |");
            }
        }
        printf(" %d\n", row);
    }

int main(){
    short size = 8;
    printCollumLabels(size);
    printBorder(size);
    for (short i = 1; i < size + 1; i++)
        {
            printRow(size,i);
            printBorder(size);
        }
    printCollumLabels(size);
    return(0);
}