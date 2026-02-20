#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song
{
    char name;
    char artist;
    struct song * nextSong;
};
struct playlist
{
    struct song * firstSong;
    short length;
};


struct playlist * initPlaylist(){
    struct playlist *pNewPlaylist = malloc(sizeof pNewPlaylist);
    pNewPlaylist->length = 0;
    return pNewPlaylist;
}
struct song * addSong(struct playlist * playlist, char artist[], char name[]){
    struct song *pCurentSong = playlist->firstSong; 
    struct song *newSong = malloc(sizeof(newSong));
    newSong->name = &name;
    newSong->artist = &artist;
    for (short index = 0; index <= playlist->length; index++)
    {
        if (index = playlist->length)
        {
            pCurentSong->nextSong = newSong;
        }
        pCurentSong = pCurentSong->nextSong;
    }
    return newSong;
}

int printPlaylist(){
    
}

struct song * deleteFirstSong(){

}
void deletePlaylist(){

}

int main(){


}