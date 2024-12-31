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
void swapSongs (Song** songs, int i, int j);
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
    Playlist* arrPlaylist = NULL;
    int playlistCounter = 0;
    int* pPlaylistCounter = &playlistCounter;
    do{
        printPlaylistsMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                watchPlaylist(&arrPlaylist, playlistCounter);
            break;
            case 2:
                addPlaylist(&arrPlaylist, pPlaylistCounter);
            break;
            case 3:
                removePlaylist(&arrPlaylist, pPlaylistCounter);
                break;
            case 4:
                freeAll(&arrPlaylist, playlistCounter);
                printf("Goodbye!\n");
            exit(0);
            default:
                printf("Invalid option\n");
        }

    } while (choice != 4);
}


void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
    return;
}

void watchPlaylistMenu() {
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. sort\n\t5. Play\n\t6. exit\n");
    return;
}

void watchPlaylist(Playlist ** arrPlaylist, int playListCounter) {
    while (TRUE) {
        // If there are no playlists
        if (playListCounter == 0) {
            printf("\t1. Back to main menu\n");
        }
        else {
            printf("Choose a playlist:\n");
            // loop that print the playlists
            for (int i =0 ; i < playListCounter; i++) {
                printf("\t%d. %s\n", i+1, arrPlaylist[i]->name);
            }
            // Add the back to menu at the end
            printf("\t%d. Back to main menu\n", playListCounter+1);
        }
        // Get the choice of which playlist the user want to access
        int choicePlaylist;
        scanf("%d", &choicePlaylist);
        // If chosen back to menu - back to menu
        if (choicePlaylist == playListCounter+1) {
            return;
        }
        // print the playlist action options
        int actionChoice;
        printf("Playlist %s:\n", (*arrPlaylist)[choicePlaylist-1].name);
        int songsCounter = 0;
        do{
            watchPlaylistMenu();
            // switch case for the action inside the Watch playlist
            scanf("%d", &actionChoice);
            switch (actionChoice) {
                case 1:
                    showPlaylist ((*arrPlaylist)+(choicePlaylist-1));
                        break;
                case 2:
                    addSong((*arrPlaylist)+(choicePlaylist-1));
                        break;
                case 3:
                    deleteSong((*arrPlaylist)+(choicePlaylist-1));
                        //freeSong();
                            break;
                case 4:
                    sortPlaylist((*arrPlaylist)+(choicePlaylist-1));
                        break;
                case 5:
                    playSong ((*arrPlaylist)+(choicePlaylist-1));
                        break;
                case 6:
                break;
                default:
                    printf("Invalid option\n");
            }

        } while (actionChoice != 6);
    }
}
// print the playlist
void showPlaylist (Playlist *playlist) {
    int peekSong;
    if (playlist->songsNum != 0) {

        // Run for the number of the song in the playlist and print title, artist, year, streams
        for (int i = 0; i < playlist->songsNum; i++) {
            printf("%d.  Title: %s\n", i+1, playlist->songs[i]->title);
            printf("    Artist: %s\n", playlist->songs[i]->artist);
            printf("    Released: %d\n", playlist->songs[i]->year);
            printf("    Streams: %d\n", playlist->songs[i]->streams);
        }
        printf("\n");

        printf("choose a song to play, or 0 to quit:\n");
        scanf("%d", &peekSong);
        while (peekSong != 0){
            scanf("%*[^\n]");
            scanf("%*c");
            printf("Now playing %s:\n", playlist->songs[peekSong-1]->title);
            printf("$ %s $\n", playlist->songs[peekSong-1]->lyrics);
            playlist->songs[peekSong-1]->streams +=1;
            printf("choose a song to play, or 0 to quit:\n");
            scanf("%d", &peekSong);
        }
    }
    else {
        printf("choose a song to play, or 0 to quit:\n");
        scanf("%d", &peekSong);
    }
    return;
}
// Func to add song to the playlist
void addSong(Playlist *playlist) {
    // clean the buffer
    scanf("%*[^\n]");
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
    return;
}
void deleteSong(Playlist* playlist) {
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
    choice -= 1;
    freeSong(playlist->songs[choice]);
    playlist->songsNum -= 1;
    for (int i = choice; i < playlist->songsNum; i++) {
        Song* temp = playlist->songs[i];
        playlist->songs[i] = playlist->songs[i+1];
    }
    printf("Song deleted successfully.\n");
}
void freeSong(Song* song) {
    free(song->title);
    free(song->artist);
    free(song->lyrics);
    free(song);
}
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
        default:
            sortByAlphabet(playlist);
            break;
    }
    printf("sorted\n");
}
void swapSongs (Song** songs, int i, int j) {
    Song *temp = songs[i];
    songs[i] = songs[j];
    songs[j] = temp;
}

void sortByYear(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            if (playlist->songs[j]->year > playlist->songs[j+1]->year)
                swapSongs(playlist->songs, j, j+1);
        }
    }
}
void sortByStreamsA(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            if (playlist->songs[j]->streams > playlist->songs[j+1]->streams)
                swapSongs(playlist->songs, j, j+1);
        }
    }
}

void sortByStreamsD(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            if (playlist->songs[j]->streams < playlist->songs[j+1]->streams)
                swapSongs(playlist->songs, j, j+1);
        }
    }
}
void sortByAlphabet(Playlist* playlist) {
    for(int i = 0; i < playlist->songsNum - 1; i++) {
        for (int j = 0; j < playlist->songsNum - i - 1; j++) {
            if (strcmp(playlist->songs[j]->title, playlist->songs[j+1]->title) > 0)
                swapSongs(playlist->songs, j, j+1);
        }
    }
}
// Func that print the songs in a playlist
void playSong(Playlist* playlist) {
    for (int i = 0; i < playlist->songsNum; i++) {
        printf("Now playing %s:\n", playlist->songs[i]->title);
        printf("$ %s $\n", playlist->songs[i]->lyrics);
        // Add one to the strean of every song
        playlist->songs[i]->streams += 1;
        printf("\n");
    }
    return;
}

void addPlaylist(Playlist** addressArrPlaylist, int *playListCounter) {
    scanf("%*[^\n]");
    scanf("%*c");
    // Realloc the array and add one place
    *addressArrPlaylist = realloc(*addressArrPlaylist, (*playListCounter + 1) * sizeof(Playlist));
    if (*addressArrPlaylist == NULL) {
        printf("Memory allocation failed for adding playlist\n");
        exit(1);
    }
    printf("Enter playlist's name:\n");
    (*addressArrPlaylist)[*playListCounter].name = takeInput();
    (*addressArrPlaylist)[*playListCounter].songsNum = 0;
    (*addressArrPlaylist)[*playListCounter].songs = NULL;
    // Add one to the counter
    *playListCounter += 1;
}

void removePlaylist(Playlist** addressArrPlaylist, int *playListCounter) {
    printf("Choose a playlist:\n");
    // loop that print the playlists
    for (int i =0 ; i < *playListCounter; i++) {
        printf("\t%d. %s\n", i+1, addressArrPlaylist[i]->name);
    }
    printf("\t%d. Back to menu\n", *playListCounter+1);
    int choice;
    scanf("%d", &choice);
    if (choice == *playListCounter+1)
        return;
    choice -= 1;
    freePlaylist(addressArrPlaylist[choice]);
    *playListCounter -= 1;
    for (int i = 0; i < *playListCounter; i++) {
        Playlist* temp = addressArrPlaylist[i];
        addressArrPlaylist[i] = addressArrPlaylist[i+1];
    }
}
void freePlaylist (Playlist* playlist) {
    for (int i = 0; i < playlist->songsNum; i++)
        freeSong(playlist->songs[i]);
    free(playlist->name);
    free(playlist->songs);
    free(playlist);
}

void freeAll (Playlist** addressArrPlaylist, int playlistCounter) {
    for (int i = 0; i < playlistCounter; i++)
        freePlaylist(addressArrPlaylist[i]);
    free(*addressArrPlaylist);
}

char* takeInput() {
    // Current size of the input (letter by letter)
    int inputCounter = 0;
    // allocate memory for the capacity of one char for the first char
    char* input = (char*) malloc(sizeof(char) + 1);
    // if malloc failed
    if (input == NULL) {
        printf("Memory allocation failed for taking input\n");
        exit(1);
    }
    char inputChar = '\0';
    // read the input char by char. till the end
    while (TRUE) {
        scanf("%c", &inputChar);
        if (inputChar == '\n')
            break;
        // Enter the char to the avillabe place
        input[inputCounter] = inputChar;
        // Add one to the size of the input
        inputCounter++;
        // reallocate more place for the next char
        input = (char*) realloc(input, (inputCounter+1) * sizeof(char));
        // If realloc failed
        if (input == NULL) {
            printf("Memory allocation failed for taking input\n");
            exit(1);
        }
    }
    // Add '\0' to the end of the string
    input[inputCounter] = '\0';
    // if nothing was input - free the memory
    if (inputCounter == 0) {
        free(input);
        return NULL;
    }
    return input;
}


