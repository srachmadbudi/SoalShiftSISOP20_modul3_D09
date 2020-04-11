# SoalShiftSISOP20_modul3_D09
```
Rachmad Budi Santoso    05111840000122
Khofifah Nurlaela       05111840000025
```

## soal1
bingung susah, semoga bisa di lain waktu.
## soal2
maaf belum bisa memberikan yg terbaik.
## soal3
kodingan bisa dilihat di folder: soal3
Kategorisasi File
Kategorisasi menerima 3 argumen
        \* untuk kategorisasi di folder dimana program tersebut berada.
        -f untuk kategorisasi file yang ditentukan.
        -d untuk kategorisasi di folder yang ditentukan.

Pembuatan direktori untuk kategorisasi berdasarkan ekstensi tiap file. Pengecekan ekstensi dan nama file menggunakan strrchr()

Dalam kategorisasi tiap file diproses dengan thread berbeda-beda.

Pemindahan file dilakukan dengan cara memmbaca file menggunakan fgetc() kemudian memasukkan ke file lain dengan nama yang sama dan folder yang berbeda menggunakan fputc().

## soal4
### soal4(a)
Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). 2. Tampilkan matriks hasil perkalian tadi ke layar. 

#### Jawaban4(a)
Create threads :
```
    while(k<4){
        err=pthread_create(&(tid[k]), NULL, &multMatrix, NULL); //pembuatan thread
        if(err != 0){
            printf("Can't create thread : [%s]\n", strerror(err));
        }
        k++;
    }
```
Join threads :
```
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
```
Perkalian matriks menggunakan threads :
```
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
```
Shared memory hasil perkalian matriks :
```
    key_t key = 1234;
    int (*value)[20];
    int shmid = shmget(key, sizeof(int)*4*5, IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
```
Menampilkan hasil perkalian matriks :
```
for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
	    printf("%d ", matrixC[i][j]);
	    *value[i * 5 +j] = matrixC[i][j];
        }
        printf("\n");
    }
```

### soal4(b)
Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar. (Catatan!: gunakan shared memory) 2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai penjumlahan n sampai 1, dan tampilkan hasilnya ke layar dengan format seperti matriks. 
Contoh: misal matriks [[5, 20, 10, 30, 50], [10, 56, 15, 18, 19], [29, 30, 11, 12, 26], ...], maka perhitungannya, untuk angka 5 adalah 5+4+3+2+1, untuk angka 20 = 20+19+18+17+...+1, dst.
### Jawaban4(b)
Untuk mendapatkan matriks hasil dari jawaban soal 4(a) :
```
    key_t key = 1234;
    int (*value)[20];
    int shmid = shmget(key, sizeof(int)*4*5, IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
	    arr[i][j] = *value[i*5+j];
	    printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
```
Create dan join threads :
```
    pthread_t tid[20];
    int index=0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++){
	    angka = arr[i][j];

            pthread_create(&tid[index], NULL, add, NULL);
            pthread_join(tid[index], NULL);
	    index++;
        }
        printf("\n");
    }

```
Untuk menghitung penjumlahan n sampai 1 setiap elemen matriks sekaligus menampilkan hasilnya pada layar:
```
   n = ((n * (n + 1)) / 2);
   printf("%d ", n);
```
# soal4(c)
Buatlah program C ketiga dengan nama "4c.c". Program ini tidak memiliki hubungan terhadap program yang lalu. Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat. (Catatan! : Harus menggunakan IPC Pipes) 
### Jawaban 4(c)
Mendefinisikan pipe dengan fork :
```
int fd1[2]; 
pid_t p; 
p = fork();
```
Pada parent proses terdapat proses untuk melist semua file dan directory yang terdapat pada directory yang sedang dibuka :
```
    close(1);
		dup(fd1[1]);
		close(fd1[0]);

		char *argv[] = {"ls", NULL};
        	execv("/bin/ls", argv);
```
Pada child proses terdapat proses untuk menghitung banyak file dan directory yang ada pada directory yang sedang dibuka :
```
    wait(NULL);
		close(0);
		dup(fd1[0]);
		close(fd1[1]);

		char *argv1[] = {"wc","-l", NULL};
        	execv("/usr/bin/wc", argv1);
```
