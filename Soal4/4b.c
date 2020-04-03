#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct matrix {
   int angka;
};

void* add(void *arg)
{
   struct matrix* data;
   data = (struct matrix*) arg;

   int n = data->angka;
   n = ((n * (n + 1)) / 2);
   printf("%d ", n);
}

int main(){

    key_t key = 1234;
    int (*value)[4][5];

    int shmid = shmget(key, sizeof(int[5][5]), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);


    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            printf("%ls ", value[i][j]);
        }
        printf("\n");
    }

    pthread_t tid[20];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++){

	    struct matrix* data = (struct matrix*)malloc(sizeof(struct matrix));
	    data->angka = value[i][j];

            pthread_create(&(tid[i * 5 + j]), NULL, add, (void*)data);
            pthread_join(tid[i * 5 + j], NULL);
        }
        printf("\n");
    }

    sleep(5);

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
