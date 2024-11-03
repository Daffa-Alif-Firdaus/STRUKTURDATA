#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

int max_size = 5;
void push(node **head, int *size);
void pop(node **head, int *size);
void stackTop(node *head);
void displayStack(node *head);
int isEmpty(node *head);
int isFull(int size);
void destroyStack(node **head, int *size);
void stackCount(int size);

int main() {
    node *head = NULL;
    char pilih;
    int size = 0;

    printf("Masukkan batas maksimum stack: ");
    scanf("%d", &max_size);

    do {
        system("cls");
        printf("=== MENU STACK ===\n");
        printf("0. Tampilkan isi stack\n");
        printf("1. Tambah data diatas (Push)\n");
        printf("2. Hapus data diatas (Pop)\n");
        printf("3. Tampilkan data teratas (Stack Top)\n");
        printf("4. Cek apakah stack kosong (Empty Stack)\n");
        printf("5. Cek apakah stack penuh (Full Stack)\n");
        printf("6. Tampilkan jumlah data di stack (Stack Count)\n");
        printf("7. Hancurkan semua data di stack (Destroy Stack)\n");
        printf("q. Keluar\n");
        printf("Pilih opsi: ");
        fflush(stdin);
        scanf(" %c", &pilih);

        switch (pilih) {
            case '0':
                displayStack(head);
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case '1':
                push(&head, &size);
                break;
            case '2':
                pop(&head, &size);
                break;
            case '3':
                stackTop(head);
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case '4':
                printf(isEmpty(head) ? "Stack kosong.\n" : "Stack tidak kosong.\n");
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case '5':
                printf(isFull(size) ? "Stack penuh.\n" : "Stack tidak penuh.\n");
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case '6':
                stackCount(size);
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case '7':
                destroyStack(&head, &size);
                printf("Stack berhasil dihapus.\n");
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
            case 'q':
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                printf("Tekan enter untuk melanjutkan...");
                getchar(); getchar();
                break;
        }
    } while (pilih != 'q');

    return 0;
}

void push(node **head, int *size) {
    if (isFull(*size)) {
        printf("Stack penuh! Tidak bisa menambah data lagi.\n");
        printf("Tekan enter untuk melanjutkan...");
        getchar(); getchar();
        return;
    }

    int bil;
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal.\n");
        printf("Tekan enter untuk melanjutkan...");
        getchar(); getchar();
        return;
    }

    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    newNode->data = bil;
    newNode->next = *head;
    *head = newNode;
    (*size)++;

    printf("Data berhasil ditambahkan ke stack.\n");
    printf("Tekan enter untuk melanjutkan...");
    getchar(); getchar();
}

void pop(node **head, int *size) {
    if (isEmpty(*head)) {
        printf("Stack kosong. Tidak ada data yang di-pop.\n");
        printf("Tekan enter untuk melanjutkan...");
        getchar(); getchar();
        return;
    }

    node *temp = *head;
    *head = (*head)->next;
    printf("Data %d berhasil di-pop dari stack.\n", temp->data);
    free(temp);
    (*size)--;
    printf("Tekan enter untuk melanjutkan...");
    getchar(); getchar();
}

void stackTop(node *head) {
    if (isEmpty(head)) {
        printf("Stack kosong.\n");
    } else {
        printf("Data teratas di stack: %d\n", head->data);
    }
}

void displayStack(node *head) {
    node *current = head;
    printf("Isi stack (top -> bottom): ");
    if (isEmpty(head)) {
        printf("Stack kosong.\n");
    } else {
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int isEmpty(node *head) {
    return head == NULL;
}

int isFull(int size) {
    return size >= max_size;
}

void destroyStack(node **head, int *size) {
    node *current = *head;
    node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
    *size = 0;
}

void stackCount(int size) {
    printf("Jumlah data di stack: %d\n", size);
}
