#include "../include/playlist.h"
#include <string.h>

int swap_songs(Song *first, Song *last){
    if (first == NULL || last == NULL) {
        return -1;
    }
    char temp_title[100];
    char temp_artist[100];

    strcpy(temp_title, first->title);
    strcpy(temp_artist, first->artist);

    strcpy(first->title, last->title);
    strcpy(first->artist, last->artist);

    strcpy(last->title, temp_title);
    strcpy(last->artist, temp_artist);

    return 0;
}

void sort_playlist_by_title(Playlist *playlist){
    int length = count_songs_recursive(playlist->p_head);
    if (length == 1 || length == 0)
    {
        return;
    }
    
    for (int index = 0; index < length - 1; index++)
    {
        Song *current = playlist->p_head->p_nextSong;
        Song *last= playlist->p_head;
        for (int index2 = 0; index2 < length - 1; index2++)
            {
                if (strcmp(current->title, last->title)>0)
                {
                    /* code */
                }
                
            }
    }
}