#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next; // Pointer ke node berikutnya
    struct node *prev; // Pointer ke node sebelumnya
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void tranverse(node *head, int reverse);
void jumlahData(node *head);
void jumlahTotal(node *head);

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di akhir\n");
        printf("3. Tambah data di tengah list\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cari data\n");
        printf("8. Cetak isi list\n");
        printf("9. Cetak isi list terbalik\n"); // Pilihan baru
        printf("10. Jumlah data dalam list\n");
        printf("T. Jumlah total dari semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch (pilih) {
            case '1': tambahAwal(&head); break;
            case '2': tambahAkhir(&head); break;
            case '3': tambahData(&head); break;
            case '4': hapusAwal(&head); break;
            case '5': hapusTengah(&head); break;
            case '6': hapusAkhir(&head); break;
            case '7': cariData(head); break;
            case '8': tranverse(head, 0); getch(); break;
            case '9': tranverse(head, 1); getch(); break; // Panggil fungsi untuk terbalik
            case '10': jumlahData(head); getch(); break;
            case 'T': jumlahTotal(head); getch(); break;
        }
    } while (pilih != 'q');

    return 0;
}

void tambahAwal(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;

        if (*head != NULL) {
            (*head)->prev = pNew; // Set previous head
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahAkhir(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            pNew->prev = NULL; // Jika list kosong
            *head = pNew;
        } else {
            node *pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->prev = pCur; // Set previous pointer
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahData(node **head) {
    int pos, bil;
    node *pNew = (node *)malloc(sizeof(node));
    node *pCur = *head;

    system("cls");
    tranverse(*head, 0);
    printf("\nposisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
        return;
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = pCur->next;
    pCur->next = pNew;
    pNew->prev = pCur;

    if (pNew->next != NULL) {
        pNew->next->prev = pNew; // Set previous pointer untuk node berikutnya
    }
}

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data untuk dihapus.");
        getch();
        return;
    }

    node *temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL; // Set previous dari head baru menjadi NULL
    }

    free(temp);
}

void hapusTengah(node **head) {
    int data;
    node *pCur = *head, *pPrev = NULL;

    if (pCur == NULL) {
        printf("List kosong.");
        getch();
        return;
    }

    printf("Masukkan nilai data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &data);

    while (pCur != NULL && pCur->data != data) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan.");
        getch();
        return;
    }

    if (pPrev == NULL) {
        *head = pCur->next; // Hapus head
        if (*head != NULL) {
            (*head)->prev = NULL; // Set previous dari head baru
        }
    } else {
        pPrev->next = pCur->next; // Hapus node tengah
        if (pCur->next != NULL) {
            pCur->next->prev = pPrev; // Set previous pointer untuk node berikutnya
        }
    }

    free(pCur);
}

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong.");
        getch();
        return;
    }

    node *pCur = *head;

    while (pCur->next != NULL) {
        pCur = pCur->next;
    }

    if (pCur->prev == NULL) {
        *head = NULL; // Hapus head jika hanya satu node
    } else {
        pCur->prev->next = NULL; // Hapus node akhir
    }

    free(pCur);
}

void cariData(node *head) {
    int data;
    node *pCur = head;

    if (pCur == NULL) {
        printf("List kosong.");
        getch();
        return;
    }

    printf("Masukkan nilai yang dicari: ");
    fflush(stdin);
    scanf("%d", &data);

    while (pCur != NULL) {
        if (pCur->data == data) {
            printf("Data %d ditemukan.\n", data);
            getch();
            return;
        }
        pCur = pCur->next;
    }

    printf("Data %d tidak ditemukan.\n", data);
    getch();
}

void tranverse(node *head, int reverse) {
    node *pWalker = head;

    if (head == NULL) {
        printf("List kosong!\n");
        return;
    }

    if (reverse == 0) {
        printf("NULL <- ");
        while (pWalker != NULL) {
            printf("%d", pWalker->data);
            if (pWalker->next != NULL) {
                printf(" <-> ");
            }
            pWalker = pWalker->next;
        }
        printf(" -> NULL\n");
    } else {
        // Traversing in reverse
        while (pWalker->next != NULL) {
            pWalker = pWalker->next; // Go to the last node
        }

        printf("NULL <- ");
        while (pWalker != NULL) {
            printf("%d", pWalker->data);
            if (pWalker->prev != NULL) {
                printf(" <-> ");
            }
            pWalker = pWalker->prev; // Move to the previous node
        }
        printf(" -> NULL\n");
    }
}

void jumlahData(node *head) {
    int count = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        count++;
        pWalker = pWalker->next;
    }
    printf("Jumlah data dalam list: %d\n", count);
}

void jumlahTotal(node *head) {
    int sum = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        sum += pWalker->data; // Add current node's data to sum
        pWalker = pWalker->next; // Move to the next node
    }

    printf("Jumlah total dari semua data: %d\n", sum);
    getch(); // Wait for user input before continuing
}
