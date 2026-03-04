#include <stdio.h>
#include "string_utils.h"


int custom_len(char *str){ // gibt die länge eines Strings ohne /n zurück -1 bei Fehler
    if (str == NULL)
    {
        return -1; // Fehler: Nullzeiger übergeben
    }
    
    char *p_current_char = str;
    int length = 0;
    while (*p_current_char != '\0')
    {
        p_current_char++;
        length++;
    }
    return length;
}

char *read_line_dynamic(){ //liest eine Zeile von der Standardeingabe ein und gibt einen Zeiger auf den dynamisch allozierten String zurück
    custom_len(fgets())
    fgets()
}


