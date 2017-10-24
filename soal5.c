#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

#define MAX_WORD 10

struct find_word_t {
    FILE *fi;
    char *word;
};

void* cariKata(void* argu);

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("Hayo kelupaan kata\n");
        return 0;
    }

    int i;
    pthread_t tid[MAX_WORD];
    struct find_word_t cari[MAX_WORD];

    FILE *fi = fopen("novel.txt", "r");

    for(i=1; i<argc; i++) {
        cari[i-1].fi = fi;
        cari[i-1].word = argv[i];
    }

    for(i=0; i<argc-1; i++)
        pthread_create(tid+i-1, NULL, &cariKata, (void *) &argv[i]);

    for(i=0; i<argc-1; i++)
        pthread_join(tid[i], NULL);
}

void* cariKata(void* argu) {
    struct find_word_t *fword = (struct find_word_t *) argu;
    printf("%s\n", fword->word);
}
