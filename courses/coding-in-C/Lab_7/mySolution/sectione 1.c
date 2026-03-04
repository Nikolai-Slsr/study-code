#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc <= 1)
    {
        printf("No arguments provided\n");
        return 1;
    }

    int *inputNumber =malloc(sizeof strtol(argv[1], NULL, 10));
    if (inputNumber == NULL)
    {
        printf("Failed to allocate memory for input number\n");
        return 1;
    }
    *inputNumber = strtol(argv[1], NULL, 10);
    printf("Input number: %d\n", *inputNumber);
    free(inputNumber);
    int *powerArray = calloc(strtol(argv[2], NULL, 10), sizeof(int));
    for (int index = 0; index < strtol(argv[2], NULL, 10); index++)
    {
        powerArray[index] = index * index;
        
    }
    // Print the power array
    printf("Power array:\n");
    for (int index = 0; index < strtol(argv[2], NULL, 10); index++)
    {        printf("%d ", powerArray[index]);
    }
    printf("\n");
    free(powerArray);
    
    return 0;
} 