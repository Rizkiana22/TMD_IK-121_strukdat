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

void start(char pita[]);
void inc(char pita[]);
char* getcw();
void makeTree(char nama_simpul[], tree *T);
void addChild(char nama_simpul[], simpul *root);
void del_simpul(simpul* root);
void del_child(simpul* target, simpul* root);
simpul* findSimpul(char nama_simpul[], simpul* root);
void printTreePreOrder(simpul *root , int level, int cabang);
void addLastK(char konsekuensi[], simpul *root);