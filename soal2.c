#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

#define FIELD_FULL (1<<16)-1
#define MAX_PLAYER 2

struct player_t {
    char *name;
    int field = 0;
    int point = 0;
};

int main() {
    int i;
    struct player_t player[MAX_PLAYER];
    char name[35];
    for(i=0; i<MAX_PLAYER; i++) {
        scanf("%s", name);
        player[i].name = name;
    }
}

