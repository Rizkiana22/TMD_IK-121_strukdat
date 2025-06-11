#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    eKolom *col;
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
void printTreePreOrder(simpul *root , int level, int indentasi[]);
void addLastK(char konsekuensi[], simpul *root);

// Struct untuk menyimpan data nilai matkul
typedef struct {
    char nama[250];
} data;

// Node dari linked list
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

void createEmpty(queue *Q);
int isEmpty(queue Q);
int countElement(queue Q);
void enqueue(char nama[], queue *Q);
void dequeue(queue *Q);
void printQueue(queue Q);

