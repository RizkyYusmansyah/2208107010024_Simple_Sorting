#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fungsi untuk menghasilkan dan menyimpan bilangan acak ke dalam file
void hasilkan_dan_simpan_bil_acak(int *arr, int ukuran, int num) {
    char nama_file[20];
    sprintf(nama_file, "%d_acak.txt", num);

    FILE *file = fopen(nama_file, "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < ukuran; i++) {
        arr[i] = rand(); // Mengisi array dengan bilangan acak
        fprintf(file, "%d\n", arr[i]); // Menulis bilangan acak ke dalam file
    }

    fclose(file);
}

// Fungsi untuk mengurutkan array menggunakan Bubble Sort
void bubble_sorting(int *arr, int ukuran) {
    for (int i = 0; i < ukuran - 1; i++) {
        for (int j = 0; j < ukuran - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j]; // Menukar elemen array jika tidak terurut
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk mengurutkan array menggunakan Selection Sort
void selection_sorting(int *arr, int ukuran) {
    int indeks_minimum, temp;
    for (int i = 0; i < ukuran - 1; i++) {
        indeks_minimum = i;
        for (int j = i + 1; j < ukuran; j++) {
            if (arr[j] < arr[indeks_minimum]) {
                indeks_minimum = j; // Mencari nilai minimum dalam array
            }
        }
        temp = arr[indeks_minimum]; // Menukar nilai minimum dengan elemen pertama yang belum terurut
        arr[indeks_minimum] = arr[i];
        arr[i] = temp;
    }
}

// Fungsi untuk mengurutkan array menggunakan Insertion Sort
void insertion_sorting(int *arr, int ukuran) {
    int kunci, j;
    for (int i = 1; i < ukuran; i++) {
        kunci = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > kunci) {
            arr[j + 1] = arr[j]; // Memindahkan elemen yang lebih besar ke posisi yang sesuai
            j = j - 1;
        }
        arr[j + 1] = kunci; // Menempatkan elemen yang disisipkan ke posisi yang sesuai
    }
}

// Fungsi untuk menyimpan array yang telah diurutkan ke dalam file beserta waktu eksekusi
void simpan_array_yang_diurutkan_ke_file(char *nama_file, int *arr, int ukuran, double waktu) {
    FILE *file = fopen(nama_file, "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "Array yang telah diurutkan:\n");
    for (int i = 0; i < ukuran; i++) {
        fprintf(file, "%d\n", arr[i]); // Menulis array yang diurutkan ke dalam file
    }

    fprintf(file, "\nWaktu Eksekusi (ms): %.2f\n", waktu); // Menulis waktu eksekusi ke dalam file

    fclose(file);
}

int main() {
    const int ukuran_maks = 1000000;
    int *arr = (int *)malloc(ukuran_maks * sizeof(int));

    printf("+-----------------+------------------+-------------------------+\n");
    printf("| Jenis Algoritma | Jumlah Bilangan  |    Waktu Eksekusi (ms)  |\n");
    printf("+=================+==================+=========================+\n");

    clock_t mulai, selesai;
    double waktu_penggunaan_cpu;

    // Pengujian dan pencatatan waktu eksekusi untuk Bubble Sort
    for (int ukuran = 100000; ukuran <= ukuran_maks; ukuran += 100000) {
        printf("| Bubble Sort         | %8dk         |", ukuran / 1000);

        hasilkan_dan_simpan_bil_acak(arr, ukuran, ukuran);

        mulai = clock();
        bubble_sorting(arr, ukuran);
        selesai = clock();

        char nama_file[20];
        sprintf(nama_file, "bubble_sort_%dk_output.txt", ukuran / 1000);
        simpan_array_yang_diurutkan_ke_file(nama_file, arr, ukuran, ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000);

        waktu_penggunaan_cpu = ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000;
        printf(" %11.2f |\n", waktu_penggunaan_cpu);
    }

    printf("+---------------------+------------------+---------------------+\n");

    // Pengujian dan pencatatan waktu eksekusi untuk Selection Sort
    for (int ukuran = 100000; ukuran <= ukuran_maks; ukuran += 100000) {
        printf("| Selection Sort      | %8dk         |", ukuran / 1000);

        hasilkan_dan_simpan_bil_acak(arr, ukuran, ukuran);

        mulai = clock();
        selection_sorting(arr, ukuran);
        selesai = clock();

        char nama_file[20];
        sprintf(nama_file, "selection_sort_%dk_output.txt", ukuran / 1000);
        simpan_array_yang_diurutkan_ke_file(nama_file, arr, ukuran, ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000);

        waktu_penggunaan_cpu = ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000;
        printf(" %11.2f |\n", waktu_penggunaan_cpu);
    }

    printf("+---------------------+------------------+---------------------+\n");

    // Pengujian dan pencatatan waktu eksekusi untuk Insertion Sort
    for (int ukuran = 100000; ukuran <= ukuran_maks; ukuran += 100000) {
        printf("| Insertion Sort      | %8dk         |", ukuran / 1000);

        hasilkan_dan_simpan_bil_acak(arr, ukuran, ukuran);

        mulai = clock();
        insertion_sorting(arr, ukuran);
        selesai = clock();

        char nama_file[20];
        sprintf(nama_file, "insertion_sort_%dk_output.txt", ukuran / 1000);
        simpan_array_yang_diurutkan_ke_file(nama_file, arr, ukuran, ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000);

        waktu_penggunaan_cpu = ((double)(selesai - mulai)) / CLOCKS_PER_SEC * 1000;
        printf(" %11.2f |\n", waktu_penggunaan_cpu);
    }

    printf("+---------------------+------------------+---------------------+\n");

    free(arr);

    return 0;
}
