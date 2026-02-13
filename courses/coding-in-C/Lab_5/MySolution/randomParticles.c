#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define alternativeLogic 1

int printCurrentState(int particleArray[], short length, int currentIteration, int mode){
    printf("%d: -->  ",currentIteration);
    for (short Index = 0; Index < length; Index++)
    {
        if (mode == 0)
        {
            printf("%d ", particleArray[Index]);
        }
        else{
            printf("%s ",(particleArray[Index] == 1)?("■"):("□")); //Print ■ for each 1 and □ for a 0
        }
        
    }
    printf("\n");
    return(0);
}

/**
 * @brief 
 * 
 * @param[out] Write_to 
 * @param[out] Copy_From 
 */
int copyArray(int particleArray[], int temp[], short length){ // use only for same length Arrays
    for (short Index = 0; Index < length; Index++)
    {
        particleArray[Index] = temp[Index];
    }
    return(0);
}

int simulationStep(int particleArray[], short length){
    int tempArray[length];
    for (int i = 0; i < length; i++) {
        tempArray[i] = 0;
    }
    for (short Index = 0; Index < length; Index++)
    {
        if(particleArray[Index] == 1){
            int randIndex;
            if(alternativeLogic == 1){
                int randomInt = rand();
                int step;
                switch (randomInt % 3) //gibt eine Pseudo-Random Zahl von 0-2
                {
                    case 0:
                        step = 1;
                        break;
                    case 1:
                        step = -1;
                        break;
                    case 2:
                        step = 0;
                        break;
                }
                randIndex = Index + step;
            }
            else
            {
                randIndex = Index  + ((rand() % 2)?(-1):(1)); //Ternärer Operator der entweder 1 oder -1 zurückgibt, abhängig davon ob eine Randomzahl gerade oder ungerade ist.            
            }
            
            if(!(randIndex < 0 || randIndex > length-1)){
                tempArray[randIndex] = 1;
            }
            else tempArray[Index] = 1;
        }   
    }
    copyArray(particleArray, tempArray, length);
    
}

int main(){
    srand(time(NULL));
    int particleArray[] = {0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1};
    short length = sizeof(particleArray) / sizeof(particleArray[0]);

    // Main Loop:
    int Iteration = 0;
    char Input[100];
    printCurrentState(particleArray, length, Iteration, 1);
    while(1){
        Iteration ++;
        fgets(Input, 100, stdin);
        printf("\n");
        simulationStep(particleArray, length);
        printCurrentState(particleArray, length, Iteration, 1);
    }
    return(0);
}