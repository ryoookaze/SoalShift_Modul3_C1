#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

struct hewan {
    int t_wait;
    int *status;
    int decrease;
};

void* hewanTunggu(void* argu);

int main() {
    int sel;
    pthread_t tid[2];
    int status[2] = {
        100,    // Lohan
        100     // Kepiting
    };

    struct hewan lohan = {10, &status[0], 15};
    struct hewan kepiting = {20, &status[1], 10};

    // They're hungry
    pthread_create(tid+0, NULL, &hewanTunggu, (void *) &lohan);
    pthread_create(tid+1, NULL, &hewanTunggu, (void *) &kepiting);

    while(1) {
        if(status[0] <= 0 || status[0] > 100 ||
            status[1] <= 0 || status[1] > 100)
            break;
        printf("Status Lohan : %d\n", status[0]);
        printf("Status Kepiting : %d\n", status[1]);
        printf("1. Kasih makan Lohan\n");
        printf("2. Kasih makan kepiting\n");
        printf("> ");
        scanf("%d", &sel);
    }


    //sleep(100);

}

void* hewanTunggu(void* argu) {
    struct hewan *hwn = (struct hewan *) argu;

    while(*hwn->status > 0 && *hwn->status <= 100) {
        //printf("%d\n", *hwn->status);
        sleep(hwn->t_wait);
        *hwn->status-=hwn->decrease;
    }
}
