#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>

int main() {
    key_t key1 = 827, key2 = 991;

    char name[6][10] = {
        "MP4A1",
        "PM2-V1",
        "SPR-3",
        "SS2-V5",
        "SPG1-V3",
        "MINE"
    };
    int *stock;

    int id1 = shmget(key1, sizeof stock, IPC_CREAT | 0666);
    stock = shmat(id1, NULL, 0);
    memset(stock, 0, sizeof(int)*6);

    int sel;
    while(1) {
    }
}
