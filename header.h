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
simpul* findSimpulJalur(char nama_simpul[], simpul* root, int level, int *kedalaman, simpul *path[]);
void HitungIndentasi(simpul *root , int level, int indentasi[]);
void printTreePreOrder(simpul *root , int level, int indentasi[], simpul *root2);
void addLastK(char konsekuensi[], simpul *root); // prosedur untuk menambahkan konsekuensi di paling akhir

/*----------Bagian Pruning----------*/
// prosedur pruning
void pruning(simpul *parent, simpul *node, int level, simpul *path[]);

/*----------Bagian Print Konsekuensi----------*/
void printKonsekuensi(simpul *path[], int kedalaman, char simpul_cari[]);


/*
Perubahan : menghapus queue karena sudah tidak diperlukan, ternyata simpul harus benar-benar dihapus
*/