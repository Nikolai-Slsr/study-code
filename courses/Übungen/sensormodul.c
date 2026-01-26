#include <stdio.h>
#include <stdbool.h>

bool uebertemperatur(char* status) {
    unsigned char temp = *status & 0b01000000;
    if (temp){return(true);}
    return(false);
}
bool unterspannung(char* status) {
    unsigned char temp = *status & 0b00100000;
    if (temp){return(true);}
    return(false);
}
bool fehler(char* status) {
    unsigned char temp = *status & 0b10000000;
    if (temp){return(true);}
    return(false);
}
unsigned char messwert(char* status){
    return(*status & 0b00001111);
}

int main(){
    unsigned char status = 0xA7;
    printf("Übertemperatur: \n %u \n", uebertemperatur(&status));
    printf("Überspannung: \n %u \n", unterspannung(&status));
    printf("Fehler: \n %u \n", fehler(&status));

    printf("Messert: \n\n %u \n", messwert(&status));
    return(0);
}
