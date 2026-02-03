#include <stdio.h>

int main(){
    int size = 8;
    for (int index = 8; index > 0; index--){
        char collum = 65;
        for (;collum < size + 64; collum++){
            printf("%c%d ",collum,index);
        }
        printf("\n");
    }
    return(0);
}