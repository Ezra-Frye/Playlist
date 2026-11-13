#pragma once
#include <string>
using namespace std;

enum class Genre {
    OTHER,       // 0
    POP,         // 1
    ROCK,        // 2
    RAP,         // 3
    JAZZ,        // 4
    CLASSICAL,   // 5
    MAX_GENRES   // 6
};
struct Song {
    string title = "missing";
    string artist = "missing";
    string album = "missing";
    Genre genre = Genre::OTHER;
    double duration = 0; // in seconds
    int release_year = 0;
    double rating = 0.0;
};

struct Playlist{
    string name = "missing";
    Genre genres [(int)Genre::MAX_GENRES];
    int num_genres = 0;
    Song* songs = nullptr;
    int num_songs = 0;
};

Playlist* createPlaylist(const string& name);
void addSong(Playlist* list, const Song song);
void addSong(Playlist* list, const string& title, const string& artist, const string& album = "missing", Genre genre = Genre::OTHER, 
double duration = 0.0, int release_year = 0, double rating = 0.0);
void removeSong(Playlist* list, const string& title);
void deletePlaylist(Playlist* list);
Playlist* filterByYear(Playlist* list, const int& year);
Playlist* filterByGenre(Playlist* list, const Genre& genre);
Playlist* filterByArtist(Playlist* list, const std::string& artistName);
Song* findSong(Playlist* list, const Song& song);