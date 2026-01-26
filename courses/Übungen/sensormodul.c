#include <stdio.h>
#include <stdbool.h>

bool uebertemperatur(char* status) {
    unsigned char temp = *status & 0b10000000;
    if (temp){return(true);}
    return(false);
}

int main(){
    unsigned char status = 0b10100111;
    printf("Übertemperatur: \n %u ", uebertemperatur(&status));
    return(0);
}
