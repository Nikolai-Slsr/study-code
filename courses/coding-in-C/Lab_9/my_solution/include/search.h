#ifndef SEARCH_H
#define SEARCH_H

#include "playlist.h"

Song *search_song_by_title(const Playlist *playlist, const char *title);

Song* find_song_recursive(Song *current, const char *title);

#endif // SEARCH_H