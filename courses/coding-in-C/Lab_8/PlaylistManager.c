#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song
{
    char name[100];
    char artist[100];
    struct song * nextSong;
};
struct playlist
{
    struct song * firstSong;
    short length;
};


struct playlist * initPlaylist(){ //returns NULL if failed, pointer to new playlist if success
    struct playlist *pNewPlaylist = malloc(sizeof *pNewPlaylist);
    if (pNewPlaylist == NULL) //edge case: if malloc failed
    {
        printf("Failed to allocate memory for new playlist\n");
        return NULL;
    }
    pNewPlaylist->length = 0;
    pNewPlaylist->firstSong = NULL;
    return pNewPlaylist;
}
struct song * addSong(struct playlist * playlist, char artist[], char name[]){ //returns NULL if failed, pointer to new song if success

    if (playlist == NULL) //edge case: if the playlist is NULL
    {
        printf("Playlist is NULL\n");
        return NULL;
    }
    
    struct song *pCurentSong = playlist->firstSong; 
    struct song *newSong = malloc(sizeof *newSong);

    if (newSong == NULL) //edge case: if malloc failed
    {
        printf("Failed to allocate memory for new song\n");
        return NULL;
    }
    strcpy(newSong->name, name); 
    strcpy(newSong->artist, artist);
    newSong->nextSong = NULL;

    if (pCurentSong == NULL) //first song in the playlist
    {
        playlist->firstSong = newSong;
        playlist->length++;
        return newSong;
    }

    for (short index = 0; index <= playlist->length; index++) //loop through the playlist to find the last song
    {
        if (pCurentSong->nextSong == NULL)
        {
            //printf("Adding song: Artist: %s, Name: %s\n", newSong->artist, newSong->name);
            pCurentSong->nextSong = newSong;
            playlist->length++;
            return newSong;
        }
        pCurentSong = pCurentSong->nextSong; //move to the next song
    }
    return NULL; //should never reach this point
}

int printPlaylist(struct playlist *pPlaylist){ // returns 0 if success, 1 if failed
    if (pPlaylist == NULL)
    {
       return 1;
    }
    
    if (pPlaylist->length == 0) //edge case: if the playlist is empty
    {
        printf("The playlist is empty\n");
        return 1;
    }
    printf("Playlist: \n");
    struct song *pCurentSong = pPlaylist->firstSong;
    for (short index = 0; index < pPlaylist->length; index++) //loop through the playlist and print each song
    {
        printf("%d. - %s  by  %s \n",index, pCurentSong->name, pCurentSong->artist);
        pCurentSong = pCurentSong->nextSong;
    }
    return 0;
}

int deleteFirstSong(struct playlist *pPlaylist){ // returns 0 if success, 1 if failed
    //get the second song in the playlist and set it as the first song, then free the memory of the first song
    // first some edge cases: if the playlist is empty or NULL, if the playlist has only one song
    if (pPlaylist == NULL || pPlaylist->firstSong == NULL)
    {
        // printf("Playlist is empty or NULL\n");
        return 1;
    }
    if (pPlaylist->firstSong->nextSong == NULL)
    {
        struct song *deletedSong = pPlaylist->firstSong;
        pPlaylist->firstSong = NULL;
        pPlaylist->length--;
        free(deletedSong);
        return 0;
    }
    //normal case: playlist has more than one song
    struct song *deletedSong = pPlaylist->firstSong;
    struct song *newFirstSong = pPlaylist->firstSong->nextSong;
    pPlaylist->firstSong = newFirstSong;
    pPlaylist->length--;
    free(deletedSong);
    return 0;
    }
void deletePlaylist(struct playlist **ppPlaylist){ // returns 0 if success, 1 if failed
    // uses double pointer to set the playlist pointer to NULL after freeing the memory of the playlist and its songs
    // this avoids dangling pointers and allows the caller to check if the playlist has been deleted by checking if the pointer is NULL
    if (ppPlaylist == NULL || *ppPlaylist == NULL) return; 
    while (deleteFirstSong(*ppPlaylist) == 0){}
    free(*ppPlaylist);
    *ppPlaylist = NULL;
}

int main(){
    //test current funtions
    struct playlist *myPlaylist = initPlaylist();
    addSong(myPlaylist, "Darci", "On My Own");
    addSong(myPlaylist, "Djo", "End of Beginning");
    addSong(myPlaylist, "Arctic Monkeys", "I Wanna Be Yours");
    addSong(myPlaylist, "Choise Atlantic", "Friends");
    addSong(myPlaylist, "Nirvana", "Come As You Are");
    addSong(myPlaylist, "Franz Ferdinand", "Take Me Out");
    addSong(myPlaylist, "The Rare Occasions", "Notion");
    addSong(myPlaylist, "Tame Impala", "The Less I Know The Better");
    addSong(myPlaylist, "The Neighbourhood", "Softcore");
    printPlaylist(myPlaylist);
    deletePlaylist(&myPlaylist);
    printPlaylist(myPlaylist);
    return 0;

}