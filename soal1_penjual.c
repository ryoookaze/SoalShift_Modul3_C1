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

    int sel, st, i;
    char na[10];
    while(1) {
        printf("MENU PENJUAL BOSS!\n");
        printf("1. Tambah stock\n");
        printf("2. List barang\n");
        printf("3. Keluar\n> ");
        scanf("%d", &sel);

        if(sel==1) {
            scanf("%s", na);
            scanf("%d", &st);
            if(!strcmp(na, name[0])) stock[0]+=st;
            if(!strcmp(na, name[1])) stock[1]+=st;
            if(!strcmp(na, name[2])) stock[2]+=st;
            if(!strcmp(na, name[3])) stock[3]+=st;
            if(!strcmp(na, name[4])) stock[4]+=st;
            if(!strcmp(na, name[5])) stock[5]+=st;
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
