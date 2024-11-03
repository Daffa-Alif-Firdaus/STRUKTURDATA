#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define MAX_MAHASISWA 20

typedef struct Mahasiswa {
    char nama[50];
    char jenis_kelamin; // 'L' untuk laki-laki, 'P' untuk perempuan
    struct Mahasiswa *next;
    struct Mahasiswa *prev;
} Mahasiswa;

Mahasiswa *headL = NULL, *headP = NULL; // Linked list untuk mahasiswa laki-laki dan perempuan
int countL = 0, countP = 0; // Menghitung jumlah laki-laki dan perempuan

// Fungsi untuk membersihkan layar konsol
void clearScreen() {
    system(CLEAR);
}

// Fungsi untuk membuat node mahasiswa baru
Mahasiswa* buatMahasiswa(char* nama, char jenis_kelamin) {
    Mahasiswa *baru = (Mahasiswa*) malloc(sizeof(Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;
    baru->next = baru->prev = baru; // Circular linked list
    return baru;
}

// Fungsi untuk menambah mahasiswa ke lingkaran
int tambahMahasiswa(char* nama, char jenis_kelamin, int kelompok) {
    // Mengecek apakah lingkaran sudah penuh
    if (countL + countP >= MAX_MAHASISWA) {
        printf("Lingkaran sudah penuh, tidak bisa menambah %s.\n", nama);
        return 0;
    }

    // Validasi Cindy, dia hanya bisa masuk ke Kelompok 2 (Perempuan) jika ada perempuan lain
    if (strcmp(nama, "Cindy") == 0 && (kelompok != 2 || countP < 1)) {
        printf("Cindy hanya bisa masuk ke kelompok perempuan jika ada perempuan lain.\n");
        return 0;
    }

    // Validasi Irsya dan Arsyad agar tidak dipisahkan dan selalu berada di kelompok laki-laki
    if ((strcmp(nama, "Irsya") == 0 || strcmp(nama, "Arsyad") == 0) && kelompok != 1) {
        printf("Irsya dan Arsyad harus berada di Kelompok 1 (Laki-laki) dan tidak boleh dipisahkan.\n");
        return 0;
    }

    Mahasiswa *baru = buatMahasiswa(nama, jenis_kelamin);

    if (kelompok == 1 && jenis_kelamin == 'L') {
        if (countL == 0) {
            headL = baru;
        } else {
            Mahasiswa *last = headL->prev;
            last->next = baru;
            baru->prev = last;
            baru->next = headL;
            headL->prev = baru;
        }
        countL++;
        return 1;
    } else if (kelompok == 2 && jenis_kelamin == 'P') {
        if (countP == 0) {
            headP = baru;
        } else {
            Mahasiswa *last = headP->prev;
            last->next = baru;
            baru->prev = last;
            baru->next = headP;
            headP->prev = baru;
        }
        countP++;
        return 1;
    } else {
        printf("Jenis kelamin tidak sesuai dengan kelompok yang dipilih.\n");
        free(baru);
        return 0;
    }
}

// Fungsi untuk menampilkan mahasiswa dalam lingkaran
void tampilLingkaran(Mahasiswa *head, int count, char *kelompok) {
    if (count == 0) {
        printf("%s kosong.\n", kelompok);
        return;
    }

    printf("%s:\n", kelompok);
    Mahasiswa *temp = head;
    int i = 0;
    do {
        printf("%d. Nama: %s, Jenis Kelamin: %c\n", i + 1, temp->nama, temp->jenis_kelamin);
        temp = temp->next;
        i++;
    } while (temp != head);
}

// Fungsi untuk menghapus mahasiswa dari lingkaran
void hapusMahasiswa(char* nama, char jenis_kelamin) {
    Mahasiswa *head = (jenis_kelamin == 'L') ? headL : headP;
    int *count = (jenis_kelamin == 'L') ? &countL : &countP;

    if (*count == 0) {
        printf("Lingkaran kosong, tidak bisa menghapus.\n");
        return;
    }

    Mahasiswa *temp = head;
    do {
        if (strcmp(temp->nama, nama) == 0) {
            if (*count == 1) {
                free(temp);
                if (jenis_kelamin == 'L') headL = NULL;
                else headP = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == head) {
                    if (jenis_kelamin == 'L') headL = temp->next;
                    else headP = temp->next;
                }
                free(temp);
            }
            (*count)--;
            printf("Mahasiswa %s berhasil dihapus dari lingkaran.\n", nama);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Mahasiswa %s tidak ditemukan.\n", nama);
}

// Fungsi untuk memastikan Irsya dan Arsyad selalu bersama
void aturIrsyaArsyad() {
    Mahasiswa *irsya = NULL, *arsyad = NULL;
    Mahasiswa *temp = headL;

    // Cari Irsya dan Arsyad
    do {
        if (strcmp(temp->nama, "Irsya") == 0) irsya = temp;
        if (strcmp(temp->nama, "Arsyad") == 0) arsyad = temp;
        temp = temp->next;
    } while (temp != headL);

    if (irsya && arsyad) {
        if (irsya->next != arsyad) {
            printf("Mengatur Irsya dan Arsyad selalu bersama.\n");
            // Menghubungkan mereka
            arsyad->prev->next = arsyad->next;
            arsyad->next->prev = arsyad->prev;

            arsyad->next = irsya->next;
            irsya->next->prev = arsyad;
            arsyad->prev = irsya;
            irsya->next = arsyad;
        }
    }
}

// Fungsi untuk memastikan Cindy bergabung dengan sesama mahasiswi
void aturCindy() {
    Mahasiswa *cindy = NULL;
    Mahasiswa *temp = headP;

    do {
        if (strcmp(temp->nama, "Cindy") == 0) {
            cindy = temp;
            break;
        }
        temp = temp->next;
    } while (temp != headP);

    if (cindy != NULL) {
        if (countP > 1) {
            printf("Cindy berhasil bergabung dengan lingkaran perempuan.\n");
        } else {
            printf("Tidak ada perempuan lain, Cindy tidak ikut.\n");
            hapusMahasiswa("Cindy", 'P');
        }
    }
}

// Fungsi untuk menampilkan menu
void tampilMenu() {
    printf("\nMenu:\n");
    printf("1. Tampilkan lingkaran mahasiswa\n");
    printf("2. Tambah mahasiswa ke lingkaran\n");
    printf("3. Hapus mahasiswa dari lingkaran\n");
    printf("4. Keluar\n");
    printf("Pilih opsi: ");
}

// Fungsi untuk inisialisasi data awal
void inisialisasiAwal() {
    tambahMahasiswa("Cindy", 'P', 2);
    tambahMahasiswa("Irsya", 'L', 1);
    tambahMahasiswa("Arsyad", 'L', 1);
    tambahMahasiswa("Dina", 'P', 2);
    tambahMahasiswa("Rudi", 'L', 1);
    tambahMahasiswa("Sari", 'P', 2);

    // Setelah penambahan, atur kondisi khusus
    aturCindy();
    aturIrsyaArsyad();
}

// Fungsi utama
int main() {
    inisialisasiAwal(); // Menambahkan data awal mahasiswa

    int pilihan;
    char nama[50], jenis_kelamin;
    int kelompok;

    do {
        clearScreen(); // Membersihkan layar sebelum menampilkan menu
        tampilMenu();
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                clearScreen(); // Bersihkan layar sebelum menampilkan hasil
                printf("\nKelompok 1 (Laki-laki):\n");
                tampilLingkaran(headL, countL, "Kelompok 1 (Laki-laki)");

                printf("\nKelompok 2 (Perempuan):\n");
                tampilLingkaran(headP, countP, "Kelompok 2 (Perempuan)");

                printf("\nTekan enter untuk melanjutkan...");
                getchar(); getchar(); // Pause agar pengguna bisa melihat output
                break;

            case 2:
                printf("Masukkan nama mahasiswa: ");
                scanf("%s", nama);
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &jenis_kelamin);
                printf("Pilih kelompok (1: Laki-laki, 2: Perempuan): ");
                scanf("%d", &kelompok);

                if (tambahMahasiswa(nama, jenis_kelamin, kelompok)) {
                    // Cek kondisi khusus
                    aturCindy();
                    aturIrsyaArsyad();
                }

                break;

            case 3:
                printf("Masukkan nama mahasiswa yang ingin dihapus: ");
                scanf("%s", nama);
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &jenis_kelamin);

                hapusMahasiswa(nama, jenis_kelamin);
                break;

            case 4:
                printf("Terima kasih, sampai jumpa lagi!\n");
                break;

            default:
                printf("Pilihan tidak valid, coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}
