#include "../include/search.h"
#include <string.h>

Song *search_song_by_title(const Playlist *playlist, const char *title){
    if(playlist == NULL || playlist->p_head == NULL){
        return NULL;
    }
    
    Song *pCurrent = playlist->p_head;

    while(pCurrent != NULL){
        if (strcmp(pCurrent->title, title) == 0)
        {
            return(pCurrent);
        }
        pCurrent = pCurrent->p_nextSong;
    }
    return NULL;
}
Song* find_song_recursive(Song *current, const char *title)
{
    if (current == NULL)
    {
        return NULL;
    }
    
    if (strcmp(current->title, title) == 0)
    {
        return(current);
    }

    return(find_song_recursive(current->p_nextSong, title));
}
