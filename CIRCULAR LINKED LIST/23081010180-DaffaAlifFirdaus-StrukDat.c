#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Deklarasi fungsi
void tambahAwal(node **pList);
void tambahData(node **pList);
void tambahAkhir(node **pList);
void hapusAwal(node **pList);
void hapusData(node **pList);
void hapusAkhir(node **pList);
void cariData(node *pList);
void hitungData(node *pList);
void jumlahData(node *pList);
void tranverse(node *pList);

int main() {
    node *pList = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("1. Tambah data di awal list\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Hapus data di awal list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir list\n");
        printf("7. Cari data list\n");
        printf("8. Hitung jumlah data list\n");
        printf("9. Hitung perjumlahan total dari semua data list\n");
        printf("t . Cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1') {
            tambahAwal(&pList);
        } else if (pilih == '2') {
            tambahData(&pList);
        } else if (pilih == '3') {
            tambahAkhir(&pList);
        } else if (pilih == '4') {
            hapusAwal(&pList);
        } else if (pilih == '5') {
            hapusData(&pList);
        } else if (pilih == '6') {
            hapusAkhir(&pList);
        } else if (pilih == '7') {
            cariData(pList);
        } else if (pilih == '8') {
            hitungData(pList);
        } else if (pilih == '9') {
            jumlahData(pList);
        } else if (pilih == 't') {
            tranverse(pList);
            getch();
        }
    } while (pilih != 'q');

    return 0;
}

// Fungsi untuk menambah data di awal list
void tambahAwal(node **pList) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*pList == NULL) {
            pNew->next = pNew; // Node menunjuk ke dirinya sendiri
            *pList = pNew; // List diupdate
        } else {
            pLast = *pList;
            while (pLast->next != *pList) {
                pLast = pLast->next; // Mencari node terakhir
            }
            pNew->next = *pList; // Node baru menunjuk ke head
            *pList = pNew; // Update head ke node baru
            pLast->next = *pList; // Node terakhir menunjuk ke head baru
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

// Fungsi untuk menambah data di tengah list
void tambahData(node **pList) {
    int pos, bil;
    node *pNew, *pCur;

    if (*pList == NULL) {
        printf("List kosong, tidak bisa tambah di tengah.");
        getch();
        return;
    }

    system("cls");
    tranverse(*pList);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *pList;
    do {
        if (pCur->data == pos) break; // Temukan posisi yang sesuai
        pCur = pCur->next;
    } while (pCur != *pList);

    if (pCur->data != pos) {
        printf("\nNode tidak ditemukan");
        getch();
    } else {
        pNew = (node *)malloc(sizeof(node));
        if (pNew != NULL) {
            pNew->data = bil;
            pNew->next = pCur->next; // Link baru ke node setelah pCur
            pCur->next = pNew; // Node pCur sekarang menunjuk ke pNew
        } else {
            printf("\nAlokasi memori gagal");
            getch();
        }
    }
}

// Fungsi untuk menambah data di akhir list
void tambahAkhir(node **pList) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*pList == NULL) {
            pNew->next = pNew; // Node menunjuk ke dirinya sendiri
            *pList = pNew; // List diupdate
        } else {
            pCur = *pList;
            while (pCur->next != *pList) {
                pCur = pCur->next; // Mencari node terakhir
            }
            pCur->next = pNew; // Node terakhir menunjuk ke node baru
            pNew->next = *pList; // Node baru menunjuk ke head
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

// Fungsi untuk menghapus data di awal list
void hapusAwal(node **pList) {
    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *temp = *pList, *pLast = *pList;

    if ((*pList)->next == *pList) { // Hanya ada satu node
        free(*pList);
        *pList = NULL; // List kosong
    } else {
        while (pLast->next != *pList) {
            pLast = pLast->next; // Mencari node terakhir
        }
        *pList = (*pList)->next; // Update head ke node berikutnya
        pLast->next = *pList; // Node terakhir menunjuk ke head yang baru
        free(temp);
    }
}

// Fungsi untuk menghapus data di tengah list
void hapusData(node **pList) {
    int bil;
    node *pCur = *pList, *pPrev = NULL;

    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    system("cls");
    tranverse(*pList);
    printf("\nMasukkan data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &bil);

    do {
        if (pCur->data == bil) break; // Temukan node yang ingin dihapus
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *pList);

    if (pCur->data != bil) {
        printf("Data tidak ditemukan.");
        getch();
        return;
    }

    if (pCur == *pList && pCur->next == *pList) {
        free(*pList); // Hanya ada satu node
        *pList = NULL; // List kosong
    } else {
        if (pCur == *pList) { // Jika node yang dihapus adalah head
            node *pLast = *pList;
            while (pLast->next != *pList) {
                pLast = pLast->next; // Mencari node terakhir
            }
            *pList = (*pList)->next; // Update head
            pLast->next = *pList; // Node terakhir menunjuk ke head yang baru
        } else {
            pPrev->next = pCur->next; // Link pPrev ke node setelah pCur
        }
        free(pCur);
    }
}

// Fungsi untuk menghapus data di akhir list
void hapusAkhir(node **pList) {
    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *pCur = *pList, *pPrev = NULL;

    if ((*pList)->next == *pList) { // Hanya ada satu node
        free(*pList);
        *pList = NULL; // List kosong
    } else {
        while (pCur->next != *pList) {
            pPrev = pCur; // Mencari node terakhir
            pCur = pCur->next;
        }
        pPrev->next = *pList; // Node sebelum terakhir menunjuk ke head
        free(pCur);
    }
}

// Fungsi untuk mencari data dalam list
void cariData(node *pList) {
    int bil;
    node *pCur = pList;

    if (pList == NULL) {
        printf("List kosong.");
        getch();
        return;
    }

    system("cls");
    tranverse(pList);
    printf("\nMasukkan data yang dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    do {
        if (pCur->data == bil) {
            printf("Data %d ditemukan.\n", bil);
            getch();
            return;
        }
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Data tidak ditemukan.\n");
    getch();
}

// Fungsi untuk menghitung jumlah data dalam list
void hitungData(node *pList) {
    int count = 0;
    node *pCur = pList;

    if (pList == NULL) {
        printf("Jumlah data dalam list: 0\n");
        getch();
        return;
    }

    do {
        count++;
        pCur = pCur->next; // Pindah ke node berikutnya
    } while (pCur != pList);

    printf("Jumlah data dalam list: %d\n", count);
    getch();
}

// Fungsi untuk menghitung jumlah total dari semua data
void jumlahData(node *pList) {
    int sum = 0;
    node *pCur = pList;

    if (pList == NULL) {
        printf("Perjumlah total dari semua data: 0\n");
        getch();
        return;
    }

    do {
        sum += pCur->data; // Tambahkan data node ke total
        pCur = pCur->next; // Pindah ke node berikutnya
    } while (pCur != pList);

    printf("Perjumlah total dari semua data: %d\n", sum);
    getch();
}

// Fungsi untuk mencetak isi list
void tranverse(node *pList) {
    node *pWalker;

    if (pList == NULL) {
        printf("List kosong.\n");
        return;
    }

    pWalker = pList;
    printf("List berisi:\n");

    // Cetak data dari head terlebih dahulu
    printf("%d -> ", pWalker->data);

    // Traverse list sampai kembali ke head
    pWalker = pWalker->next; // Mulai dari node berikutnya
    while (pWalker != pList) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }

    // Cetak kembali head
    printf("%d\n", pList->data); // Cetak head terakhir
}
