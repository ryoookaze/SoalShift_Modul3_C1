#include<stdio.h>
#include<pthread.h>
#include<string.h>

#define LL long long

void* faktorial(void* n);
int convertToInt(const char *str);

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("Kelupaan nomor hayo");
        return 0;
    }

    printf("%d\n", convertToInt(argv[1]));

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
