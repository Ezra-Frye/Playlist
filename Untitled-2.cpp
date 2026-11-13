//how to do things for Comp Test 

// create a pointer to an array 
    Playlist* createPlaylist (const std::string name){
        Playlist* list = new Playlist: // you create a pointer then assign an array, you can create the array in the same line with "new"
        list -> name = name; // access parts of an array from a pointer with -> 
        return list;
    }
// Delete a pointer to an array (delete the playlist)
     void deletePlaylist( ){
            // you want to delete any of the vectors/array's within the thing your deleteing first and then the rest of the array
            if(list->songs != nullptr){ // if the playlist is already empty it won't delete anything 
                delete [] list -> songs; // delete [] ___ -> allows you to delete things within in the array
                list -> songs = nullptr; // replace what you delete with a nullptr always
            }
            delete list; 
            list = nullptr;

        }
//add something to an array 
    void addSong(Playlist* list, const Song song){ //
    if (!list) return;

    Song* new_songs = new Song[list->num_songs + 1]; // creates a new array that is one larger to include the added song
    for (int i = 0; i < list->num_songs; i++){ // Copies old songs into new array
        new_songs[i] = list->songs[i];
    }
    new_songs[list->num_songs] = song; // puts new song into the new array

    delete[] list->songs; // deletes the old array, gets rid of the old list of songs8
    list->songs = new_songs; // puts the new songs into the playlist 
    list->num_songs++; // updates the amount of songs 

    // Add song's genre to playlist if not already present
    addGenreIfMissing(list, song.genre);
}

void addSong(Playlist* list, const string& title, const string& artist, // You want to use two functions, one to add a song to the array and one to put a spesifc song into th playlist
             const string& album, Genre genre,  double duration,  int release_year,  double rating){
    Song song = {title, artist, album, genre, duration, release_year, rating}; //infuse a new array with stuff from parameters
    addSong(list, song); // uses the first function to actually add the song
}
// remove from an array
void removeSong(Playlist* list, const string& title){
    if (!list || list->num_songs == 0) return; // if there are no songs dont do anything

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
        delete[] list->songs; // delete all songs in the array
        list->songs = nullptr; //fill empty array
        list->num_songs = 0; //set number of songs to zero
        list->num_genres = 0; 
        return;
    }

    // Create array with 1 fewer element
    Song* new_songs = new Song[list->num_songs - 1]; // create a new pointer to a new array with a smaller song array
    for (int i = 0, j = 0; i < list->num_songs; i++) { // goes through each song in the playlist
        if (i != match_index) { // if the song is not the index of the song you want to remove 
            new_songs[j++] = list->songs[i]; // add it to the new pointer 
        }
    }

    delete[] list->songs; // delete the songs off of the playlist
    list->songs = new_songs; // add the revised playlist's songs into the the playlist's songs
    list->num_songs--; // decrease the # of songs in the playlist

    // Recalculate remaining unique genres
    updatePlaylistGenres(list);
}
//finding a speisfic term
Song* findSong(Playlist* list, const Song& song) {
    if (!list) return nullptr;

    for (int i = 0; i < list->num_songs; i++) {
        if (list->songs[i].title == song.title) {
            return &(list->songs[i]); // Return address of existing song
        }
    }
    return nullptr; // Return nullptr if not found
}
//sorting an array into a new array
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

// enum class vs. class
    // emum class creates a list of named integers
    // class