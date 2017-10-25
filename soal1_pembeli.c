#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>

int main() {
    key_t key1 = 827;

    char name[6][10] = {
        "MP4A1",
        "PM2-V1",
        "SPR-3",
        "SS2-V5",
        "SPG1-V3",
        "MINE"
    };
    int *stock;

    int id1 = shmget(key1, sizeof(int), IPC_CREAT | 0666);
    stock = shmat(id1, NULL, 0);
    memset(stock, 0, sizeof(int)*6);

    int sel, st, i;
    char na[10];
    while(1) {
        printf("MENU PEMBELI BOSS!\n");
        printf("1. Beli barang\n");
        printf("2. List barang\n");
        printf("3. Keluar\n> ");
        scanf("%d", &sel);

        if(sel==1) {
            scanf("%s", na);
            scanf("%d", &st);
            for(i=0; i<6; i++) {
                if(!strcmp(na, name[i])) {
                    if(stock[i]-st>=0) {
                        stock[i]-=st;
                        printf("Sukses dibeli\n");
                    }
                    else
                        printf("Kekurangan barang boss\n");
                }
            }
        }
        else if(sel==2) {
            printf("\nSTOCK BARANG\n");
            for(i=0; i<6; i++) {
                if(stock[i]>0)
                    printf("%s %d\n", name[i], stock[i]);
            }
            printf("\n");
        }
        else if(sel==3) break;
        else {
            printf("Salah\n");
            continue;
        }
    }
}
