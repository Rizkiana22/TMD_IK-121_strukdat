#include "header.h"

int main() {
    tree T;
    char nama_simpul[250];
    char nama_ortu[250];
    char nama_konsekuensi[250];
    int jumlah_konsekuensi;

    char pita[300]; // membuat array dengan panjang 300
    int n;
    scanf("%d", &n);
    simpul *cari = NULL;
    for(int i = 0; i < n; i++){
        scanf(" %[^#\n]#%[^#\n]#%d", nama_simpul, nama_ortu, &jumlah_konsekuensi);

        if(strcmp(nama_ortu, "null") == 0){
            makeTree(nama_simpul, &T);
            if(T.root != NULL){
                for(int j = 0; j < jumlah_konsekuensi; j++){
                    scanf("%s", nama_konsekuensi);
                    addLastK(nama_konsekuensi, T.root);
                }
            }
        }else{
            cari = findSimpul(nama_ortu, T.root);
            if(cari != NULL){
                addChild(nama_simpul, cari);
                cari = findSimpul(nama_simpul, T.root);
                for(int j = 0; j < jumlah_konsekuensi; j++){
                    scanf("%s", nama_konsekuensi);
                    addLastK(nama_konsekuensi, cari);
                }
            }
        }


    }
    int indentasi[100] = {0};
    HitungIndentasi(T.root, 0, indentasi);
    printTreePreOrder(T.root, 0, indentasi);

    
    return 0;
}