#include "code.h"
#include <string>

using namespace std;

Playlist* createPlaylist(const string& name){
    Playlist* list = new Playlist; 
    list->name = name; 
    list->songs = nullptr;
    list->num_songs = 0;
    list->num_genres = 0;
    return list;
}

// Helper function: Check if a genre exists in playlist->genres
static bool hasGenre(const Playlist* list, Genre genre) {
    for (int i = 0; i < list->num_genres; i++) {
        if (list->genres[i] == genre) {
            return true;
        }
    }
    return false;
}

// Helper function: Add genre if it's not already in the playlist
static void addGenreIfMissing(Playlist* list, Genre genre) {
    if (!hasGenre(list, genre) && list->num_genres < static_cast<int>(Genre::MAX_GENRES)) {
        list->genres[list->num_genres] = genre;
        list->num_genres++;
    }
}

// Helper function: Rebuild the genres list based on current songs
static void updatePlaylistGenres(Playlist* list) {
    list->num_genres = 0;
    for (int i = 0; i < list->num_songs; i++) {
        addGenreIfMissing(list, list->songs[i].genre);
    }
}

void addSong(Playlist* list, const Song song){
    if (!list) return;

    Song* new_songs = new Song[list->num_songs + 1];
    for (int i = 0; i < list->num_songs; i++){
        new_songs[i] = list->songs[i];
    }
    new_songs[list->num_songs] = song;

    delete[] list->songs;
    list->songs = new_songs;
    list->num_songs++;

    // Add song's genre to playlist if not already present
    addGenreIfMissing(list, song.genre);
}

void addSong(Playlist* list, 
             const string& title, 
             const string& artist, 
             const string& album, 
             Genre genre, 
             double duration, 
             int release_year, 
             double rating){
    Song song = {title, artist, album, genre, duration, release_year, rating};
    addSong(list, song);
}

void removeSong(Playlist* list, const string& title){
    if (!list || list->num_songs == 0) return;

    // Find the index of the first song matching the title
    int match_index = -1;
    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].title == title) {
            match_index = i;
            break;
        }
    }

    // If song not found, do nothing
    if (match_index == -1) return;

    // If it's the only song in the playlist
    if (list->num_songs == 1) {
        delete[] list->songs;
        list->songs = nullptr;
        list->num_songs = 0;
        list->num_genres = 0;
        return;
    }

    // Create array with 1 fewer element
    Song* new_songs = new Song[list->num_songs - 1];
    for (int i = 0, j = 0; i < list->num_songs; i++) {
        if (i != match_index) {
            new_songs[j++] = list->songs[i];
        }
    }

    delete[] list->songs;
    list->songs = new_songs;
    list->num_songs--;

    // Recalculate remaining unique genres
    updatePlaylistGenres(list);
}

void deletePlaylist(Playlist* list){
    if (!list) return;

    if (list->songs != nullptr){
        delete[] list->songs;
        list->songs = nullptr; 
    }

    delete list;
}

Song* findSong(Playlist* list, const Song& song) {
    if (!list) return nullptr;

    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].title == song.title) {
            return &(list->songs[i]); // Return address of existing song
            // Song* ptrSong = &(list->songs[i]);
            // return ptrSong;
        }
    }
    return nullptr; // Return nullptr if not found
}

Playlist* filterByArtist(Playlist* list, const std::string& artistName){
    if (!list) return nullptr;
    Playlist* filtered = createPlaylist("Filtered");

    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].artist == artistName) {
        addSong(filtered, list->songs[i]);     
    }
    }
   return filtered;
}

Playlist* filterByGenre(Playlist* list, const Genre& genre){
    if (!list) return nullptr;
    Playlist* filtered = createPlaylist("Filtered");

    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].genre == genre) {
        addSong(filtered, list->songs[i]);     
    }
    }
   return filtered;
}

Playlist* filterByYear(Playlist* list, const int& year){
    if (!list) return nullptr;
    Playlist* filtered = createPlaylist("Filtered");

    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].release_year == year) {
        addSong(filtered, list->songs[i]);     
    }
    }
   return filtered;
}