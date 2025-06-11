#include "header.h"

int main() {
    tree T;
    queue Q;
    createEmpty(&Q);
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
    scanf("%s", nama_simpul);
    int indentasi[100] = {0};
    HitungIndentasi(T.root, 0, indentasi);
    printTreePreOrder(T.root, 0, indentasi);
    simpul *print[100];
    int kedalaman;

    print[0] = T.root;
    simpul *cek = findSimpulPrint(nama_simpul, T.root, 1, &kedalaman, print);
    if(cek != NULL){
        int spasi = 0;
        for(int i = 0; i <= kedalaman; i++){
            for(int i = 0; i < spasi; i++){
                printf(" ");
            }
            printf("[-%s-]\n", print[i]->kontainer.nama_simpul);

            int panjangSimpul = strlen(print[i]->kontainer.nama_simpul);
            eKolom *eCol = print[i]->col;
            int panjangKolom = 0;
            while(eCol != NULL){
                if(panjangKolom < strlen(eCol->kontainer_kol.konsekuensi)){
                    panjangKolom = strlen(eCol->kontainer_kol.konsekuensi);
                }
                for(int i = 0; i < spasi; i++){
                    printf(" ");
                }
                enqueue(eCol->kontainer_kol.konsekuensi, &Q);
                printf(" -%s\n", eCol->kontainer_kol.konsekuensi);
                eCol = eCol->next_kol;
            }
            if(panjangKolom + 3 > panjangSimpul + 6){
                spasi += panjangKolom + 3;
            }else{
                spasi += panjangSimpul + 6;
            }
            printf("\n");
        }
    }else{
        printf("LMAO\n");
    }
    printf("Konsekuensi yang Dijalani dengan Pilihan %s:\n", nama_simpul);
    printQueue(Q);
    return 0;
}