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

void checkGame(struct player_t *a, struct player_t *b);

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
        player[i].point = 0;
        player[i].field = 0;
    }

    struct player_zip pzip1 = {&player[0], &player[1]};
    struct player_zip pzip2 = {&player[1], &player[0]};

    pthread_create(tid+0, NULL, &playerOneTurn, (void *) &pzip1);
    pthread_create(tid+1, NULL, &playerTwoTurn, (void *) &pzip2);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    printf("kasdahsdhj");

    while(player[0].status!=0) continue;

    if(player[0].point>player[1].point)
        printf("%s wins the game!\n", player[0].name);
    else if(player[1].point>player[0].point)
        printf("%s wins the game!\n", player[1].name);
    else
        printf("Game is draw!\n");


}

void* playerOneTurn(void* argu) {
    struct player_zip *pzip = (struct player_zip *) argu;
    struct player_t *play1 = pzip->play1;
    struct player_t *play2 = pzip->play2;

    int n_mine, mine, i;
    while(1) {
        while(*play1->status != 1) continue; // Player 2's turn
        if(play1->point >= 10 || play2->point >= 10 ||
            (play1->field == FIELD_FULL && play2->field == FIELD_FULL)) {
            checkGame(play1, play2);
            exit(EXIT_SUCCESS);
        }

        printf("Current score:\n");
        printf("\t%s : %d\n", play1->name, play1->point);
        printf("\t%s : %d\n", play2->name, play2->point);

        printf("%s's turn to put mines in their field\n", play1->name);
        printf("\tNumber of mine : ");
        scanf("%d", &n_mine);
        printf("\tWhere to put mine? ");
        for(i=0; i<n_mine; i++) {
            scanf("%d", &mine);
            play1->field = play1->field | (1<<(mine-1));
        }

        fflush(stdout);
        system("clear");

        printf("It's time for %s to guess where the mines are.\n", play2->name);
        printf("\tGuesses : ");
        for(i=0; i<4; i++) {
            scanf("%d", &mine);

            // There's mine :(
            if(play1->field & (1<<(mine-1)))
                play1->point++;

            // Nope
            else
                play2->point++;
        }

        fflush(stdout);
        system("clear");

        *play1->status = -1;
    }
}

void* playerTwoTurn(void* argu) {
    struct player_zip *pzip = (struct player_zip *) argu;
    struct player_t *play1 = pzip->play1;
    struct player_t *play2 = pzip->play2;

    int n_mine, mine, i;
    while(1) {
        while(*play1->status != -1) continue; // Player 1's turn
        if(play1->point >= 10 || play2->point >= 10 ||
            (play1->field == FIELD_FULL && play2->field == FIELD_FULL)) {
            checkGame(play2, play1);
            exit(EXIT_SUCCESS);
        }

        printf("Current score:\n");
        printf("\t%s : %d\n", play2->name, play2->point);
        printf("\t%s : %d\n", play1->name, play1->point);

        printf("%s's turn to put mines in their field\n", play1->name);
        printf("\tNumber of mine : ");
        scanf("%d", &n_mine);
        printf("\tWhere to put mine? ");
        for(i=0; i<n_mine; i++) {
            scanf("%d", &mine);
            play1->field = play1->field | (1<<(mine-1));
        }

        fflush(stdout);
        system("clear");

        printf("It's time for %s to guess where the mines are.\n", play2->name);
        printf("\tGuesses : ");
        for(i=0; i<4; i++) {
            scanf("%d", &mine);

            // There's mine :(
            if(play1->field & (1<<(mine-1)))
                play1->point++;

            // Nope
            else
                play2->point++;
        }

        fflush(stdout);
        system("clear");

        *play1->status = 1;
    }
}

void checkGame(struct player_t *a, struct player_t *b) {
    if(a->point>b->point)
        printf("%s wins the game!\n", a->name);
    else if(b->point>a->point)
        printf("%s wins the game!\n", b->name);
    else
        printf("The game is draw\n");
}



