#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

pthread_t tid[4]; //inisisasi banyaknya thread (dalam kasus ini 4 thread)
pid_t child;

//inisialisasi matrix
int matrixA[4][2] = {{1,4}, {3,1}, {2,1}, {1,3}};
int matrixB[2][5] = {{1,2,1,3,2}, {2,4,2,0,5}};
int matrixC[4][5];

void *multMatrix(void *arg) {
    pthread_t id = pthread_self();
    if(pthread_equal(id, tid[0])){  //baris 1 matrix C
        for (int i=0; i<5; i++) {
            matrixC[0][i] = (matrixA[0][0]*matrixB[0][i]) + (matrixA[0][1]*matrixB[1][i]);
        }
    }else if(pthread_equal(id, tid[1])){ //baris 2 matrix C
        for (int i=0; i<5; i++) {
            matrixC[1][i] = (matrixA[1][0]*matrixB[0][i]) + (matrixA[1][1]*matrixB[1][i]);
        }
    }else if(pthread_equal(id, tid[2])){ //baris 3 matrix C
        for (int i=0; i<5; i++) {
            matrixC[2][i] = (matrixA[2][0]*matrixB[0][i]) + (matrixA[2][1]*matrixB[1][i]);
        }
    }else if(pthread_equal(id, tid[3])){ //baris 4 matrix C
        for (int i=0; i<5; i++) {
            matrixC[3][i] = (matrixA[3][0]*matrixB[0][i]) + (matrixA[3][1]*matrixB[1][i]);
        }
    }
}

int main(){
    int k=0, err;

    key_t key = 1234;
    int *value;
    int shmid = shmget(key, sizeof(int[4][5]), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);

    while(k<4){
        err=pthread_create(&(tid[k]), NULL, &multMatrix, NULL); //pembuatan thread
        if(err != 0){
            printf("Can't create thread : [%s]\n", strerror(err));
        }
        k++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }

    sleep(5);

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
