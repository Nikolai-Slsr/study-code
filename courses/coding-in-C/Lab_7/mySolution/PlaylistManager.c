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
    playlist->length++;
    return newSong;
}

int printPlaylist(struct playlist *pPlaylist){
    if (pPlaylist->length == 0)
    {
        printf("The playlist is empty");
        return 1;
    }
    struct song *pCurentSong = pPlaylist->firstSong;
    for (short index = 0; index < pPlaylist->length; index++)
    {
        printf("Artist: %s, Name: %s", pCurentSong->artist, pCurentSong->name);
        pCurentSong = pCurentSong->nextSong;
    }
}

struct song * deleteFirstSong(){

}
void deletePlaylist(){

}

int main(){
    //test current funtions
    struct playlist *myPlaylist = initPlaylist();
    addSong(myPlaylist, "Artist1", "Name1");
    addSong(myPlaylist, "Artist2", "Name2");
    printPlaylist(myPlaylist);

}