#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

void printPlaylistsMenu();
void watchPlaylistMenu();
void watchPlaylist(Playlist ** arrPlaylist, int playListCounter);
void showPlaylist (Playlist *playlist);
void addSong(Playlist *playlist);
void deleteSong(Playlist* playlist);
void freeSong(Song* song);
void sortPlaylist(Playlist *playlist);
void swapSongs(Playlist* playlist, int i, int j);
void sortByYear(Playlist* playlist);
void sortByStreamsA(Playlist* playlist);
void sortByStreamsD(Playlist* playlist);
void sortByAlphabet(Playlist* playlist);
void playSong(Playlist* playlist);
void addPlaylist(Playlist** addressArrPlaylist, int *playListCounter);
void removePlaylist(Playlist** addressArrPlaylist, int *playListCounter);
void freePlaylist (Playlist* playlist);
void freeAll (Playlist** addressArrPlaylist, int playlistCounter);
char* takeInput();
int main() {
    int choice = 0;
    // An array of the playlist addresses
    Playlist* arrPlaylist = NULL;
    // counter for how many playlists I have
    int playlistCounter = 0;
    int* pPlaylistCounter = &playlistCounter;
    do{
        printPlaylistsMenu();
        scanf("%d", &choice);
        // switch case for the main menu (action on the main library)
        switch (choice) {
            case 1:
                // Watch playlist and enter the actions on specific playlist
                watchPlaylist(&arrPlaylist, playlistCounter);
            break;
            case 2:
                addPlaylist(&arrPlaylist, pPlaylistCounter);
            break;
            case 3:
                removePlaylist(&arrPlaylist, pPlaylistCounter);
                break;
            case 4:
                // Free all the allocations before exiting
                freeAll(&arrPlaylist, playlistCounter);
                printf("Goodbye!\n");
                return 0;
            // If invalid input has entered
            default:
                printf("Invalid option\n");
        }
    // repeat as long as 4 wasnt entered and then it will exit there
    } while (TRUE);
}

// print the main menu
void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}
// print the specific playlist action menu
void watchPlaylistMenu() {
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. sort\n\t5. Play\n\t6. exit\n");
}
// // Watch playlist and enter the actions on specific playlist
void watchPlaylist(Playlist ** arrPlaylist, int playListCounter) {
    while (TRUE) {
        // If there are no playlists
        if (playListCounter == 0) {
            printf("Choose a playlist:\n");
            printf("\t1. Back to main menu\n");
        }
        else {
            printf("Choose a playlist:\n");
            // loop that print the playlists
            for (int i =0 ; i < playListCounter; i++) {
                printf("\t%d. %s\n", i+1, (*arrPlaylist)[i].name);
            }
            // Add the back to menu at the end
            printf("\t%d. Back to main menu\n", playListCounter+1);
        }
        // Get the choice of which playlist the user want to access
        int choicePlaylist;
        scanf("%d", &choicePlaylist);
        while (choicePlaylist <= 0 || choicePlaylist > playListCounter+1){
            printf("Invalid option\n");
            printf("Choose a playlist:\n");
            scanf("%d",&choicePlaylist);
        }
        // If chosen back to menu - back to menu
        if (choicePlaylist == playListCounter+1) {
            return;
        }
        // print the playlist action options
        choicePlaylist -= 1;
        int actionChoice;
        printf("Playlist %s:\n", (*arrPlaylist)[choicePlaylist].name);
        //int songsCounter = 0;
        do{
            watchPlaylistMenu();
            // switch case for the action inside the Watch playlist
            scanf("%d", &actionChoice);
            switch (actionChoice) {
                case 1:
                    // show the songs in the playlist and play inside
                    showPlaylist ((*arrPlaylist)+(choicePlaylist));
                break;
                case 2:
                    // add song to the playlist
                    addSong((*arrPlaylist)+(choicePlaylist));
                break;
                case 3:
                    // delete song from the playlist
                    deleteSong((*arrPlaylist)+(choicePlaylist));
                break;
                case 4:
                    // sort the songs
                    sortPlaylist((*arrPlaylist)+(choicePlaylist));
                break;
                case 5:
                    // play all the songs
                    playSong ((*arrPlaylist)+(choicePlaylist));
                break;
                // exit back to choose a playlist
                case 6:
                    break;
                default:
                    printf("Invalid option\n");
            }
        // repeat until 6 (exit) was entered
        } while (actionChoice != 6);
    }
}
// print the playlist and play songs if wanted
void showPlaylist (Playlist *playlist) {
    int pickSong;
    // print only if there are songs in the playlist
    if (playlist->songsNum != 0) {
        // Run for the number of the songs in the playlist and print title, artist, year, streams
        for (int i = 0; i < playlist->songsNum; i++) {
            printf("%d.  Title: %s\n", i+1, playlist->songs[i]->title);
            printf("    Artist: %s\n", playlist->songs[i]->artist);
            printf("    Released: %d\n", playlist->songs[i]->year);
            printf("    Streams: %d\n", playlist->songs[i]->streams);
        }
        printf("\n");
        printf("choose a song to play, or 0 to quit:\n");
        scanf("%d", &pickSong);
        // play a picked song
        // play until 0 was entered
        while (pickSong != 0){
            // if invalid input was given
            if (pickSong < 0 || pickSong > playlist->songsNum+1) {
                printf("Invalid input\n");
                scanf("%d", &pickSong);
            }
            //print the name of the song and its lyrics, add one to the streans
            else {
                printf("Now playing %s:\n", playlist->songs[pickSong-1]->title);
                printf("$ %s $\n", playlist->songs[pickSong-1]->lyrics);
                playlist->songs[pickSong-1]->streams +=1;
                printf("choose a song to play, or 0 to quit:\n");
                scanf("%d", &pickSong);
            }
        }
    }
    // if there arent songs inside the playlist
    else {
        printf("choose a song to play, or 0 to quit:\n");
        scanf("%d", &pickSong);
    }
}
// Func to add song to the playlist
void addSong(Playlist *playlist) {
    // clean the buffer
    scanf("%*[^ \n]");
    scanf("%*c");
    // increment the number of song in 1
    playlist->songsNum += 1;
    // Update the memory allocation to the new size of the number of songs
    playlist->songs = realloc(playlist->songs, (playlist->songsNum)*sizeof(Song));
    // If memory allocation failed - exit
    if(playlist->songs == NULL) {
        printf("Memory allocation failed for adding song\n");
        exit(1);
    }
    // Allocate memory to the song detail inside the arry
    playlist->songs[playlist->songsNum - 1] = malloc(sizeof(Song));
    //If memory allocation failed - exit
    if (playlist->songs[playlist->songsNum - 1] == NULL) {
        printf("Memory allocation failed for the song\n");
        exit(1);
    }
    // get the detail of the song
    printf("Enter song's details\n");
    // Get title using take input func
    printf("Title:\n");
    playlist->songs[playlist->songsNum-1]->title = takeInput();
    // Get the artist
    printf("Artist:\n");
    playlist->songs[playlist->songsNum-1]->artist = takeInput();
    // Get the year
    printf("Year of release:\n");
    scanf("%d", &playlist->songs[playlist->songsNum-1]->year);
    //clean the buffer
    scanf("%*[^ \n]");
    scanf("%*c");
    // Get the lyrics
    printf("Lyrics:\n");
    playlist->songs[playlist->songsNum-1]->lyrics = takeInput();
    // Initialize the streams to 0
    playlist->songs[playlist->songsNum-1]->streams = 0;
}
// Func that delete the song
void deleteSong(Playlist* playlist) {
    // print the songs
    for (int i = 0; i < playlist->songsNum; i++) {
        printf("%d.  Title: %s\n", i+1, playlist->songs[i]->title);
        printf("    Artist: %s\n", playlist->songs[i]->artist);
        printf("    Released: %d\n", playlist->songs[i]->year);
        printf("    Streams: %d\n", playlist->songs[i]->streams);
    }
    printf("choose a song to delete, or 0 to quit:\n");
    int choice;
    scanf("%d", &choice);
    if (!choice)
        return;
    while (choice < 0 || choice > playlist->songsNum+1) {
        // if invalid input was given
        printf("Invalid input\n");
        scanf("%d", &choice);
    }
    // accord the choice to the array places
    choice -= 1;
    // free that the allocation that the song is pointing at
    freeSong(playlist->songs[choice]);
    // subtract one from the number of songs
    playlist->songsNum -= 1;
    // shift the songs to fill the deleted spot
    for (int i = choice; i < playlist->songsNum; i++) {
        playlist->songs[i] = playlist->songs[i+1];
    }
        printf("Song deleted successfully.\n");
}
// free the song itself
void freeSong(Song* song) {
    free(song->title);
    free(song->artist);
    free(song->lyrics);
    free(song);
}
// Func to sort the playlist in different ways
void sortPlaylist(Playlist *playlist) {
    printf(("choose:\n"));
    printf("1. sort by year\n");
    printf("2. sort by streams - ascending order\n");
    printf("3. sort by streams - descending order\n");
    printf("4. sort alphabetically\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            sortByYear(playlist);
            break;
        case 2:
            sortByStreamsA(playlist);
            break;
        case 3:
            sortByStreamsD(playlist);
            break;
        case 4:
            sortByAlphabet(playlist);
            break;
        // if any other number that is not in the menu was given - sort by alphabet
        default:
            sortByAlphabet(playlist);
            break;
    }
    printf("sorted\n");
}
// func that swap the songs due to the indexes that given
void swapSongs(Playlist* playlist, int i, int j) {
    // temp to save the value in index i
    Song* temp = playlist->songs[i];
    // i is now j
    playlist->songs[i] = playlist->songs[j];
    // j is temp (origin i)
    playlist->songs[j] = temp;
}
// Bubble sort func that sort by year
void sortByYear(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            // if the year in an index is greater than the next one - swap
            if (playlist->songs[j]->year > playlist->songs[j+1]->year)
                swapSongs(playlist, j, j+1);
        }
    }
}
// Bubble sort func that sort by ascending streams
void sortByStreamsA(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            // if the streams in an index is greater than the next one - swap
            if (playlist->songs[j]->streams > playlist->songs[j+1]->streams)
                swapSongs(playlist, j, j+1);
        }
    }
}
// Bubble sort func that sort by descending streams
void sortByStreamsD(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            // if the streams in an index is greater than the next one - swap
            if (playlist->songs[j]->streams < playlist->songs[j+1]->streams)
                swapSongs(playlist, j, j+1);
        }
    }
}
// Bubble sort func that sort by alphabet
void sortByAlphabet(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            // if the title in an index is greater than the next one (meaning not in alphabetically order) - swap
            if (strcmp(playlist->songs[j]->title, playlist->songs[j+1]->title) > 0)
                swapSongs(playlist, j, j+1);
        }
    }
}
// Func that play the playlist - print the all songs and the lyrics in a playlist
void playSong(Playlist* playlist) {
    // run for the size of the songs in the playlist
    for (int i = 0; i < playlist->songsNum; i++) {
        printf("Now playing %s:\n", playlist->songs[i]->title);
        printf("$ %s $\n", playlist->songs[i]->lyrics);
        // Add one to the stream of every song
        playlist->songs[i]->streams += 1;
        printf("\n");
    }
}
// Func that add a playlist
void addPlaylist(Playlist** addressArrPlaylist, int *playListCounter) {
    // clean the buffer
    scanf("%*[^ \n]");
    scanf("%*c");
    // Realloc one more place to the array
    *addressArrPlaylist = realloc(*addressArrPlaylist, (*playListCounter + 1) * sizeof(Playlist));
    // if realloc failed
    if (*addressArrPlaylist == NULL) {
        printf("Memory allocation failed for adding playlist\n");
        exit(1);
    }
    printf("Enter playlist's name:\n");
    // take an input for the name
    (*addressArrPlaylist)[*playListCounter].name = takeInput();
    // initialize the number of songs in the playlist to 0
    (*addressArrPlaylist)[*playListCounter].songsNum = 0;
    // initialize the pointer to the songs array to NULL
    (*addressArrPlaylist)[*playListCounter].songs = NULL;
    // Add one to the counter
    *playListCounter += 1;
}
// func that remove and free a playlist
void removePlaylist(Playlist** addressArrPlaylist, int* playListCounter) {
    printf("Choose a playlist:\n");
    // loop that print the playlists
    for (int i =0 ; i < *playListCounter; i++) {
        printf("\t%d. %s\n", i+1, (*addressArrPlaylist)[i].name);
    }
    printf("\t%d. Back to main menu\n", *playListCounter+1);
    int choice;
    scanf("%d", &choice);
    // if invalid input was given - rescan
    while (choice <= 0 || choice > *playListCounter+1){
        printf("Invalid option\n");
        printf("Choose a playlist:\n");
        scanf("%d",&choice);
    }
    // if choosed to return to menu
    if (choice == *playListCounter+1)
        return;
    // accord the choice of the user to the way of the computer (start with 0)
    choice -= 1;
    // free the playlist
    freePlaylist((*addressArrPlaylist)+choice);
    // subtract one from the playlist counter
    *playListCounter -= 1;
    // shift the array to fill the removed spot
    for (int i = choice; i < *playListCounter; i++) {
        (*addressArrPlaylist)[i] = (*addressArrPlaylist)[i+1];
    }
    // if there were playlist realloc a new place to save the deleted playlist
    if (*playListCounter > 0) {
        *addressArrPlaylist = realloc(*addressArrPlaylist, (*playListCounter)*sizeof(Playlist));
        // if realloc failed
        if (*addressArrPlaylist == NULL) {
            printf("failed to reallocate memory\n");
            exit(1);
        }
    printf("re allocated\n");
    }
}
// Func that free the playlist
void freePlaylist (Playlist* playlist) {
    // free the songs inside first
    for (int i = 0; i < playlist->songsNum; i++)
        freeSong(playlist->songs[i]);
    // free the name
    free(playlist->name);
    // free the array
    free(playlist->songs);
}
// Func that free everything before exiting
void freeAll (Playlist** addressArrPlaylist, int playlistCounter) {
    // free all the playlists
    for (int i = 0; i < playlistCounter; i++) {
        freePlaylist(&(*addressArrPlaylist)[i]);
    }
    // free the playlists array
    free(*addressArrPlaylist);
}
char* takeInput() {
    // Current size of the input (letter by letter)
    int inputCounter = 1;
    // allocate memory for the capacity of one char for the first char
    char* input = NULL;
    char inputChar = '\0';
    // read the input char by char. till the end ('\n')
    while (TRUE) {
        scanf("%c", &inputChar);
        if (inputChar == '\n')
            break;
        // reallocate more place for the next char
        input = (char*) realloc(input, (inputCounter+1) * sizeof(char));
        // If realloc failed
        if (input == NULL) {
            printf("Memory allocation failed for taking input\n");
            exit(1);
        }
        // change '\r' to '\0'
        if (inputChar == '\r')
            inputChar = '\0';
        // Enter the char to the available place
        input[inputCounter-1] = inputChar;
        // Add one to the size of the input
        inputCounter++;
    }
    // Add '\0' to the end of the string
    input[inputCounter-1] = '\0';
    // if nothing was input - free the memory
    if (inputCounter == 1) {
        return NULL;
    }
    return input;
}