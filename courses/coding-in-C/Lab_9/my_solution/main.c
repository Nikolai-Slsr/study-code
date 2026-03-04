/*
 * File: main.c
 * Description: Program to demo usage of playlist
 */
#include "include/playlist.h"
#include "include/search.h"
/**
 * @brief exemplary usage of playlist
 *
 * @return int status code
 */
int main(void)
{
    printf("\nMaximum playlist size is set to %d songs.\n", MAX_SONGS);
    Playlist myPlaylist;
    Song *p_foundSong = NULL;
    init_playlist(&myPlaylist);

    add_song(&myPlaylist, "Crawling", "Linkin Park");
    add_song(&myPlaylist, "Layla", "Eric Clapton");
    add_song(&myPlaylist, "Esperanto", "Max Herre");
    print_playlist(&myPlaylist);

    p_foundSong = find_song_recursive(myPlaylist.p_head, "Layla");
    if (p_foundSong != NULL)
    {
        printf("\nSearch hit: %s by %s\n", p_foundSong->title, p_foundSong->artist);
    }
    else
    {
        printf("\nSearch miss: Layla\n");
    }

    p_foundSong = find_song_recursive(myPlaylist.p_head, "Numb");
    if (p_foundSong != NULL)
    {
        printf("Search hit: %s by %s\n", p_foundSong->title, p_foundSong->artist);
    }
    else
    {
        printf("Search miss: Numb\n");
    }

    delete_firstSong(&myPlaylist);
    print_playlist(&myPlaylist);

    delete_playlist(&myPlaylist);

    return 0;
}
