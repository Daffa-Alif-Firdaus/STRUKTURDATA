#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void tranverse(node *head);
void jumlahData(node *head);
void jumlahTotal(node *head);
void insertNode(node **head, node *pPre, node *pNew);

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
        printf("9. Jumlah data dalam list\n");
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
            case '8': tranverse(head); getch(); break;
            case '9': jumlahData(head); getch(); break;
            case 'T': jumlahTotal(head); getch(); break;
        }
    } while (pilih != 'q');

    return 0;
}

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
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
    } else {
        pPrev->next = pCur->next; // Hapus node tengah
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
    node *pPrev = NULL;

    while (pCur->next != NULL) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pPrev == NULL) {
        *head = NULL; // Hapus head
    } else {
        pPrev->next = NULL; // Hapus node akhir
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

void tranverse(node *head) {
    node *pWalker = head;
    system("cls");
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL");
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
        switch (1) { // Dummy switch for demonstration
            case 1:
                sum += pWalker->data; // Add current node's data to sum
                break;
        }
        pWalker = pWalker->next; // Move to the next node
    }

    printf("Jumlah total dari semua data: %d\n", sum);
    getch(); // Wait for user input before continuing
}
