#include<stdio.h>
#include<pthread.h>

#define LL unsigned long long

LL faktorial(int n);
int convertToInt(char *str);

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("Kelupaan nomor hayo");
        return 0;
    }


}

LL faktorial(int n) {
    int i;
    LL prod = 1;
    for(i=1; i<=n; i++) prod*=i;
    return prod;
}
