#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*----------Bagian N-er Tree----------*/
// struct isi nama simpul
typedef struct{
    char nama_simpul[250]; 
}data_simpul;

// strcut isi nama konsekuensi
typedef struct{
    char konsekuensi[250];
}data_konsekuensi;

// struct yang berisi konsekuensi
typedef struct eklm *alamatekolom; 
typedef struct eklm { 
    data_konsekuensi kontainer_kol; 
    alamatekolom next_kol; 
} eKolom;

// strcut yang berisi informasi simpul
typedef struct smp *alamatsimpul;
typedef struct smp {
    data_simpul kontainer;
    eKolom *col; // pointer linked list ke konsekuensi
    alamatsimpul sibling;
    alamatsimpul child;
} simpul;

typedef struct {
    simpul *root;
} tree;

void makeTree(char nama_simpul[], tree *T);
void addChild(char nama_simpul[], simpul *root);
void del_simpul(simpul* root);
void del_child(simpul* target, simpul* root);
simpul* findSimpul(char nama_simpul[], simpul* root);
simpul* findSimpulPrint(char nama_simpul[], simpul* root, int level, int *kedalaman, simpul *print[]);
void HitungIndentasi(simpul *root , int level, int indentasi[]);
void printTreePreOrder(simpul *root , int level, int indentasi[], simpul *root2);
void addLastK(char konsekuensi[], simpul *root); // prosedur untuk menambahkan konsekuensi di paling akhir

/*----------Bagian Queue----------*/
// Struct untuk menyimpan data queue
typedef struct {
    char nama[250];
} data;

// struct elemen queue
typedef struct elm *alamatelmt;
typedef struct elm {
    data kontainer;
    alamatelmt next;
} elemen;

// Struct untuk queue
typedef struct {
    elemen *first;
    elemen *last;
} queue;

// prosedur fungsi queue
void createEmpty(queue *Q);
int isEmpty(queue Q);
int countElement(queue Q);
void enqueue(char nama[], queue *Q);
void dequeue(queue *Q);
void printQueue(queue Q);

/*----------Bagian Pruning----------*/
// prosedur pruning
void pruning(char simpul_cari[250], simpul *root, int *kedalaman, simpul *path[], queue Q);

