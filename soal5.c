#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

#define MAX_WORD 10

struct find_word_t {
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

    for(i=1; i<argc; i++) {
        cari[i-1].word = argv[i];
    }

    for(i=0; i<argc-1; i++)
        pthread_create(tid+i, NULL, &cariKata, (void *) &cari[i]);

    for(i=0; i<argc-1; i++)
        pthread_join(tid[i], NULL);
}

void* cariKata(void* argu) {
    struct find_word_t *fword = (struct find_word_t *) argu;
    int count = 0;
    char buffer[256];
    FILE *he = fopen("novel.txt", "r");

    while(fgets(buffer, 256, he) != NULL) {
        char *buff = buffer;
        while(buff = strstr(buff, fword->word)) {
                count++;
                buff++;
        }
    }

    printf("%s : %d\n", fword->word, count);
    fclose(he);
}
