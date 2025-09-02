/*Saya Muhammad Rizkiana Pratama dengan NIM 2404421 mengerjakan tugas masa depan dalam mata kuliah struktur data dan algoritma 
untuk keberkahan-Nya maka saya tidak akan melakukan kecurangan seperti yang telah di spesifikasikan*/

#include "header.h"

/*Analisis big O:
1. Input simpul sebanyak n dengan konsekuensi sebanyak m dan Menambahkan simpul dan konsekuensi ke dalam tree menggunakan DFS :
    untuk menambahkan simpul perlu menggunakan find_simpul (DFS) 
    find_simpul dijalankan untuk mencari posisi tempat penambahan 
    kasus terburuknya bisa butuh mengunjungi semua simpul maka O(n) karena simpul input sebanyak n, maka input simpul O(n^2 + m)
2. Hitung indentasi :
    hitung indentasi memiliki kompleksitas O(n + m) n = banyak simpul m = banyak konsekuensi, panjang konsekuensi dihitung juga
3. Print tree :
    print tree memiliki kompleksitas O(n + m) n = banyak simpul m = banyak konsekuensi
4. Pruning :
    pruning menggunakan DFS yang berarti O(n) n = banyak simpul
5. Print Konsekuensi :
    printkonsekuensi memiliki kompleksitas O(m) m = banyak konsekuensi

kesimpulan :
Program saya memiliki total kompleksitas O(n^2 + m) n = banyak simpul m = banyak konsekuensi
*/
int main() {
    // inisialisasi struktur data
    tree T;

    // inisialisasi variabel untuk input
    char nama_simpul[250];
    char nama_ortu[250];
    char nama_konsekuensi[250];
    int jumlah_konsekuensi;


    int n; // jumlah input simpul
    scanf("%d", &n); // isi jumlah input simpul

    simpul *cari = NULL; // inisialisasi simpul cari
    for(int i = 0; i < n; i++){
        scanf(" %[^#\n]#%[^#\n]#%d", nama_simpul, nama_ortu, &jumlah_konsekuensi); // input simpul, simpul ortu, dan jumlah konsekuensi
        if(strcmp(nama_ortu, "null") == 0){ // jika nama ortu 'null', maka make tree
            makeTree(nama_simpul, &T); // buat ner tree
            if(T.root != NULL){
                for(int j = 0; j < jumlah_konsekuensi; j++){ // isi konsekuensi
                    scanf("%s", nama_konsekuensi); // isi konsekuensi
                    addLastK(nama_konsekuensi, T.root); // tambahkan ke akhir kolom
                }
            }
        }else{ // menambahkan simpul baru
            cari = findSimpul(nama_ortu, T.root); // mencari simpul ortu
            if(cari != NULL){ // jika simpul ortu ditemukan
                addChild(nama_simpul, cari); // tambah simpul baru
                cari = findSimpul(nama_simpul, T.root); // cari simpul baru
                for(int j = 0; j < jumlah_konsekuensi; j++){ // isi konsekuensi sebanyak jumlah konsekuensi
                    scanf("%s", nama_konsekuensi); // isi konsekuensi
                    addLastK(nama_konsekuensi, cari); // tambahkan ke akhir kolom
                }
            }
        }


    }
    char simpul_cari[250]; // inisialisasi variabel untuk mencari simpul target
    scanf("%s", simpul_cari); // mengisi simpul_cari


    int indentasi[100] = {0}; // array untuk menyimpan jumlah spasi atau indentasi per level 
    HitungIndentasi(T.root, 0, indentasi); // menghitung indentasi atau jumlah spasi per level 
    printTreePreOrder(T.root, 0, indentasi, T.root); // print Tree dengan modifikasi indentasi

    // mencari jalur ke target
    simpul *path[100]; // array simpul untuk menyimpan simpuljalur ke target
    int kedalaman = 0; // variabel untuk menghitung seberapa dalam atau berapa simpul ke target
    if(T.root != NULL){ // jika tree ada
        path[0] = T.root; // menyimpan root atau simpul pertama ke array path
        simpul *cek = findSimpulJalur(simpul_cari, T.root, 1, &kedalaman, path); // cari jalur ke simpul target (nanti jalur disimpan di array path)
        if(cek != NULL){
            pruning(NULL, T.root, 0, path); // pruning tree untuk menyisakan simpul jalur ke target
            int indentasi2[100] = {0}; // array untuk menyimpan jumlah spasi atau indentasi setelah pruning per level 
            HitungIndentasi(T.root, 0, indentasi2); // hitung indentasi tree setelah pruning
            printTreePreOrder(T.root, 0, indentasi2, T.root); // print Tree dengan modifikasi indentasi
            printKonsekuensi(path, kedalaman, simpul_cari); // print daftar konsekuensi
        }
    }
    return 0;
}