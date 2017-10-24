#include<stdio.h>
#include<pthread.h>
#include<string.h>

#define LL long long
#define MAX_VAL 10

void* faktorial(void* n);
int convertToInt(const char *str);

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("Kelupaan nomor hayo");
        return 0;
    }

    int i;
    int N[MAX_VAL];

    // Put each argv to int[]
    for(i=1; i<argc; i++)
        N[i-1] = convertToInt(argv[i]);

    pthread_t tid[MAX_VAL];

    for(i=0; i<argc-1; i++)
        pthread_create(tid+i, NULL, &faktorial, (void *) &N[i]);

    for(i=0; i<argc-1; i++)
        pthread_join(tid[i], NULL);

}

void* faktorial(void* n) {
    int i;
    LL prod = 1;
    int *k = n;
    printf("Hasil %d! = ", *k);
    for(i=1; i<=*k; i++) prod*=i;
    printf("%lld\n", prod);
}

int convertToInt(const char *str) {
    int sum = 0, i;
    int len = strlen(str);
    for(i=0; i<len; i++)
        sum = sum*10 + ((int)str[i] - 48);
    return sum;
}
