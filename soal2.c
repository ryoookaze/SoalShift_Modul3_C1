#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

#define FIELD_FULL (1<<16)-1
#define MAX_PLAYER 2

void* playerOneTurn(void* argu);
void* playerTwoTurn(void* argu);

struct player_t {
    char name[35];
    int field;
    int point;
    int *status;
};

struct player_zip {
    struct player_t *play1;
    struct player_t *play2;
};

int main() {
    int i;
    struct player_t player[MAX_PLAYER];
    char name[35];
    int status = 1; // pseudo-mutex for turn, player 1 first
    pthread_t tid[2];

    player[0].status = &status;
    player[1].status = &status;

    for(i=0; i<MAX_PLAYER; i++) {
        printf("Insert Player %d's name : ", i+1);
        scanf("%s", name);
        strcpy(player[i].name, name);
    }

    struct player_zip pzip1 = {&player[0], &player[1]};
    struct player_zip pzip2 = {&player[1], &player[0]};

    pthread_create(tid+0, NULL, &playerOneTurn, (void *) &pzip1);
    pthread_create(tid+0, NULL, &playerTwoTurn, (void *) &pzip2);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);




}

void* playerOneTurn(void* argu) {
    struct player_zip *pzip = (struct player_zip *) argu;
    struct player_t *play1 = pzip->play1;
    struct player_t *play2 = pzip->play2;

    printf("Current score:\n");
    printf("\t%s : %d\n", play1->name, play1->point);
    printf("\t%s : %d\n", play2->name, play2->point);

    int n_mine, mine, i;
    while(1) {
        while(*play1->status != 1) continue; // Player 2's turn
        printf("%s's turn to put mines in their field\n", play1->name);
        printf("\tNumber of mine : ");
        scanf("%d", &n_mine);
        printf("\tWhere to put mine? ");
        for(i=0; i<n_mine; i++) {
            scanf("%d", &mine);
            play1->field = play1->field | (1<<(mine-1));
        }
        sleep(2);
        *play1->status = -1;
    }
}

void* playerTwoTurn(void* argu) {
    struct player_zip *pzip = (struct player_zip *) argu;
    struct player_t *play1 = pzip->play1;
    struct player_t *play2 = pzip->play2;

    while(1) {
        while(*play1->status != -1) continue; // Player 2's turn
        printf("%s's turn to put mines in %s's field\n", play1->name, play2->name);
        //printf("Player 2 bos\n");
        sleep(2);
        *play1->status = 1;
    }
}





