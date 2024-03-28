#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song
{
    char title[100];
    char artist[100];
    char duration[10];
    Song *next;
    Song *prev;
} *head, *tail;

Song *createSong(const char *title, const char *artist, const char *duration){
    Song *newSong = (Song*)malloc(sizeof(Song));

    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->duration, duration);
    newSong->next = NULL;
    newSong->prev = NULL;

    return newSong;
}

void pushHead(const char *title, const char *artist, const char *duration){
    Song *temp = createSong(title, artist, duration);

    if(!head){
        head = tail = temp;
    }
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

// Push Tail
void insertSong(const char *title, const char *artist, const char *duration){
    Song *temp = createSong(title, artist, duration);
    
    if(!head){
        head = tail = temp;
    }
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void insertAfter(const char *target, const char *title, const char *artist, const char *duration){
    Song *newSong = createSong(title, artist, duration);

    if(!head){
        printf("Target not found!\n");
        // head = tail = NULL;
    }
    else {
        Song *temp = head;
        while (temp){
            if(strcmp(target, temp->title) == 0){
                // temp == tail
                if(temp == tail){
                    tail->next = newSong;
                    newSong->prev = tail;
                    tail = newSong;
                }
                else {
                    Song *left = temp;
                    Song *right = temp->next;
                    left->next = newSong;
                    newSong->prev = left;
                    newSong->next = right;
                    right->prev = newSong;
                }
                printf("Song '%s' inserted after '%s'.\n", newSong->title, temp->title);
                return;
            }
            temp = temp->next;
        }
        printf("Target song not found!\n");
    }
}

void insertBefore(const char *target, const char *title, const char *artist, const char *duration){
    Song *newSong = createSong(title, artist, duration);

    if(!head){
        printf("Target song not found!\n");
    }
    else {
        if(strcmp(head->title, target) == 0){
            newSong->next = head;
            head->prev = newSong;
            head = newSong;
            return;
        }
        else {
            Song *temp = head;
            while (temp){
                if(strcmp(temp->title, target) == 0){
                    Song *left = temp->prev;
                    Song *right = temp;
                    left->next = newSong;
                    newSong->prev = left;
                    newSong->next = right;
                    right->prev = newSong;
                    printf("Song '%s' inserted before '%s'.\n", newSong->title, temp->title);
                    return;
                }
                temp = temp->next;
            }
            printf("Target song not found!\n");
        }
    }
}

void showPlaylist(){
    printf("Playlist:\n");

    Song *curr = head;
    while(curr != NULL){
        printf("Title: %s | Artist: %s | Duration: %s\n", curr->title, curr->artist, curr->duration);
        curr = curr->next;
    }
}

void popHead(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        Song *temp = head->next;
        head->next = NULL;
        temp->prev = NULL;
        head = temp;
        free(head);
    }
}

void popTail(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        Song *temp = tail->prev;
        tail->prev = NULL;
        temp->next = NULL;
        tail = temp;
        free(tail);
    }
}

void removeSong(const char *title){
    if(!head){
        printf("Playlist is empty.\n");
    }
    else if(strcmp(head->title, title) == 0){
        popHead();
    }
    else if(strcmp(tail->title, title) == 0){
        popTail();
    }
    else {
        printf("Song '%s' removed from the Playlist.\n", title);
        Song *curr = head;
        while(strcmp(curr->title, title) != 0){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->next = NULL;
        curr->prev = NULL;
        free(curr);
    }
}

void clearPlaylist(){
    printf("Playlist Cleared!\n");
    while(head){
        popHead();
    }
}

int main(){

    insertSong("Song Title 1", "Artist 1", "03.30");
    insertSong("Song Title 2", "Artist 2", "04.15");
    insertSong("Song Title 3", "Artist 3", "02.50");
    insertSong("Song Title 4", "Artist 4", "05.00");

    showPlaylist();

    insertAfter("Song Title 2", "Song Title 2.5", "Artist 2.5", "01.45");
    insertBefore("Song Title 4", "Song Title 3.5", "Artist 3.5", "02.30");

    showPlaylist();

    removeSong("Song Title 2.5");
    removeSong("Song Title 4");

    clearPlaylist();

    showPlaylist();

    return 0;
}