#include "header.h"

void makeTree(char nama_simpul[], tree *T) { // prosedur membuat tree
    simpul *node = (simpul *)malloc(sizeof(simpul));
    strcpy(node->kontainer.nama_simpul, nama_simpul);
    node->sibling = NULL;
    node->child = NULL;
    node->col = NULL;
    (*T).root = node;
}

void addChild(char nama_simpul[], simpul *root) {
    if (root != NULL) {
        /* jika simpul root tidak kosong, berarti dapat ditambahkan simpul anak */
        simpul *baru = (simpul *)malloc(sizeof(simpul));
        strcpy(baru->kontainer.nama_simpul, nama_simpul);
        baru->child = NULL;
        baru->col = NULL;

        if (root->child == NULL) {
            /* jika simpul root belum memiliki simpul anak 
            maka simpul baru menjadi anak pertama */
            baru->sibling = NULL;
            root->child = baru;
        } else {
            if (root->child->sibling == NULL) {
                /* jika simpul root memiliki 
                anak yang belum memiliki saudara, maka 
                simpul baru menjadi anak kedua */
                baru->sibling = root->child;
                root->child->sibling = baru;
            } else {
                simpul *last = root->child;
                /* mencari simpul anak terakhir 
                karena akan dikaitkan dengan simpul 
                baru sebagai simpul anak terakhir yang 
                baru, simpul anak terakhir adalah yang 
                memiliki sibling simpul anak pertama, 
                maka selama belum sampai pada simpul 
                anak terakhir, penunjuk last akan 
                berjalan ke simpul anak berikutnya */
                while (last->sibling != root->child) {
                    last = last->sibling;
                }
                baru->sibling = root->child;
                last->sibling = baru;
            }
        }
    }
}

void del_simpul(simpul* root){
    // cek kondisi jika root ada
    if (root != NULL) {
        // cek kondisi jika root (parent) punya anak
        if (root->child != NULL) {
            // kondisi ketika hanya ada satu anak di root
            if (root->child->sibling == NULL) {
                del_simpul(root->child); // Rekursif hapus simpul ke anak
            }else{ // kondisi ketika lebih dari satu anak di root
                simpul* current; // pointer untuk iterasi
                simpul* target; // pointer untuk simpul yang akan dihapus

                // inisialisasi current dengan anak pertama
                current = root->child;
        
                // Loop untuk menghapus semua anak sampai kembali ke anak pertama (sekuential)
                while (current->sibling != root->child) {
                    target = current;
                    current = current->sibling;
                    del_simpul(target); // hapus simpul target secara rekursif
                }
                // Hapus anak terakhir (yang belum terhapus di dalam loop)
                if (current != NULL){
                    del_simpul(current);
                }
            }
        }
        // Setelah semua anak dihapus, hapus simpul root itu sendiri
        free(root);
    }
}

void del_child(simpul* target, simpul* root){
    // kondisi ketika root ada
    if (root != NULL && target != NULL) {
        simpul* current = root->child;
        if (current != NULL) {
            // kondisi ketika hanya ada satu anak
            if (current->sibling == NULL) {
                // kondisi ketika anak merupakan target yang mau dihapus
                if (root->child == target) {
                    del_simpul(root->child);
                    root->child = NULL; // Set child to NULL
                } else
                    printf("[!] Node %s has only one child (%s) and it's not the target", root->kontainer.nama_simpul, root->child->kontainer.nama_simpul);
            }else { // kondisi ketika lebih dari satu anak
                simpul* prev = NULL; // inisialisasi pointer prev dengan NULL
                int found = 0; // set var found = 0 (flag)

                // loop sampai semua anak dicek (sampai anak pertama)
                while (current->sibling != root->child && found == 0) {
                    // jika target ditemukan
                    if (current == target)
                        found = 1;
                    else {
                        prev = current;
                        current = current->sibling;
                    }
                }

                // cek apakah anak terakhir adalah simpul target yang ingin dihapus
                if (current == target && found == 0)
                    found = 1; // tandai bahwa target ditemukan
                if (found == 1) {
                    simpul* last = root->child;

                    // mencari anak terakhir
                    while (last->sibling != root->child) {
                        last = last->sibling;
                    }

                    // Jika prev == NULL, berarti simpul target adalah anak pertama
                    if (prev == NULL) {
                        // Kondisi ketika ada 2 anak dan target adalah anak pertama
                        if (current->sibling == last && last->sibling == root->child) {
                            root->child = last;
                            last->sibling = NULL;
                        }else { // Kondisi ketika ada lebih dari 2 anak dan target adalah anak pertama
                            root->child = current->sibling;
                            last->sibling = root->child;
                        }
                    }else{ // jika target bukan anak pertama
                        // Mencari anak kedua untuk memeriksa apakah hanya ada 2 anak
                        simpul* second_child = root->child->sibling;
                        // kondisi ketika target adalah anak terakhir dan hanya ada 2 anak
                        if (prev == root->child && second_child->sibling == root->child) {
                            root->child->sibling = NULL; // putuskan pointer ke sibling (tinggal satu anak)
                        }
                        // kondisi ketika target adalah anak terakhir dan ada lebih dari 2 anak
                        else {
                            prev->sibling = current->sibling;
                            current->sibling = NULL; // putuskan sibling simpul
                        }
                    }
                    // hapus simpul target
                    del_simpul(current);
                } else{
                    printf("[!] Node with the name %s is not found", target->kontainer.nama_simpul);
                }
            }
        }
    }
}


simpul* findSimpul(char nama_simpul[], simpul* root){ // function mencari simpul target
    simpul* result = NULL;
    // kondisi ketika root ada
    if (root != NULL) {
        // jika target ditemukan di root
        if (strcmp(root->kontainer.nama_simpul, nama_simpul) == 0)
            result = root;
        else { // jika target bukan root (berarti target anak cucunya)
            simpul* current = root->child;
            // Cek apakah root punya anak
            if (current != NULL) {
                // jika current hanya satu anak
                if (current->sibling == NULL) {
                    if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0)
                        result = current; // isi result dengan current
                    else{
                        result = findSimpul(nama_simpul, current); // Jika bukan, cari secara rekursif di anak
                    }
                }else {
                    int found = 0;
                    // Jika memiliki lebih dari satu anak
                    while (current->sibling != root->child && found == 0) {
                        // Found condition
                        if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0){
                            result = current;
                            found = 1;
                        }else {// jika tidak ditemukan, cari ke anak
                            result = findSimpul(nama_simpul, current);
                            current = current->sibling;
                            if (result != NULL){
                                found = 1;
                            }
                        }
                    }
                    // proses anak terakhir
                    if (found == 0) {
                        if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0)
                            result = current; // Found condition
                        else{
                            result = findSimpul(nama_simpul, current); // jika tidak ditemukan cari lagi secara rekursif
                        }
                    }
                }
            }
        }
    }
    return result; // mengembalikan hasil
}

simpul* findSimpulPrint(char nama_simpul[], simpul* root, int level, int *kedalaman, simpul *print[]){ // function mencari simpul target
    simpul* result = NULL;
    // kondisi ketika root ada
    if (root != NULL) {
        // jika target ditemukan di root
        if (strcmp(root->kontainer.nama_simpul, nama_simpul) == 0){
            result = root;
        }else{ // jika target bukan root (berarti target anak cucunya)
            simpul* current = root->child;
            // Cek apakah root punya anak
            if (current != NULL) {
                // jika current hanya satu anak
                print[level] = current;
                *kedalaman = level;
                if (current->sibling == NULL) {
                    if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0)
                        result = current; // isi result dengan current
                    else{
                        result = findSimpulPrint(nama_simpul, current, level + 1, kedalaman, print); // Jika bukan, cari secara rekursif di anak
                    }
                }else {
                    int found = 0;
                    // Jika memiliki lebih dari satu anak
                    while (current->sibling != root->child && found == 0) {
                        // Found condition
                        if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0){
                            result = current;
                            found = 1;
                        }else {// jika tidak ditemukan, cari ke anak
                            result = findSimpulPrint(nama_simpul, current, level + 1, kedalaman, print);
                            current = current->sibling;
                            if (result != NULL){
                                found = 1;
                            }
                        }
                    }
                    // proses anak terakhir
                    if (found == 0) {
                        if (strcmp(current->kontainer.nama_simpul, nama_simpul) == 0){
                            // print[level] = root;
                            // *kedalaman = level; 
                            result = current; // Found condition
                        }
                        else{
                            result = findSimpulPrint(nama_simpul, current, level + 1, kedalaman, print); // jika tidak ditemukan cari lagi secara rekursif
                        }
                    }
                }
            }
        }
    }
    return result; // mengembalikan hasil
}

void addFirstK(char konsekuensi[], simpul *root) {     
    eKolom *baru;   
    baru = (eKolom *) malloc(sizeof(eKolom));   
    strcpy(baru->kontainer_kol.konsekuensi, konsekuensi);             
    

    if((*root).col == NULL) {     
        baru->next_kol = NULL;   
    } else {         
        baru->next_kol = (*root).col;   
    }   
    
    (*root).col = baru;   
    baru = NULL;    
}

void addAfterK(eKolom *prev, char konsekuensi[]) {      
    eKolom *baru; 
    baru = (eKolom *) malloc(sizeof(eKolom)); 
    strcpy(baru->kontainer_kol.konsekuensi, konsekuensi); 
    

    if(prev->next_kol == NULL) {      
        baru->next_kol = NULL; 
    } else { 
        baru->next_kol = prev->next_kol;   
    }   
    
    prev->next_kol = baru;   
    baru = NULL;   
}

void addLastK(char konsekuensi[], simpul *root) { 
    if((*root).col == NULL) {     
        /* jika list adalah list kosong */     
        addFirstK(konsekuensi, root); 
    } else {     
        /* jika list tidak kosong */     
        /* mencari elemen terakhir list */      
        eKolom *last = (*root).col;  
        while(last->next_kol != NULL) {       
            /* iterasi */       
            last = last->next_kol;           
        }     
        addAfterK(last, konsekuensi); 
    }  
}

void HitungIndentasi(simpul *root , int level, int indentasi[]){ // print tree preorder dengan indentasi dan cabang (final revisi)
    if (root != NULL) {
        int panjangSimpul = strlen(root->kontainer.nama_simpul);
        eKolom *eCol = root->col;
        while(eCol != NULL){
            int panjangKolom = strlen(eCol->kontainer_kol.konsekuensi);
            if(indentasi[level] < panjangKolom + 3){
                indentasi[level] = panjangKolom + 3;
            }
            eCol = eCol->next_kol;
        }
        if(indentasi[level] < panjangSimpul + 6){
            indentasi[level] = panjangSimpul + 6;
        }
        simpul *bantu = root->child; // isi pointer bantu dengan child untuk loop
        if (bantu != NULL) {
            if (bantu->sibling == NULL) {
                /* jika memiliki satu simpul anak */
                HitungIndentasi(bantu, level + 1, indentasi); // rekursif
            } else {
                /* jika memiliki banyak simpul anak */
                /* mencetak simpul anak */
                
                while (bantu->sibling != root->child) {
                    HitungIndentasi(bantu, level + 1, indentasi);
                    bantu = bantu->sibling;
                }
                /* memproses simpul anak terakhir karena belum terproses dalam pengulangan */
                HitungIndentasi(bantu, level + 1, indentasi); // rekursif
            }
        }
    }
}

void printTreePreOrder(simpul *root , int level, int indentasi[]){ // print tree preorder dengan indentasi dan cabang (final revisi)
    if (root != NULL) { 
        for (int i = 0; i < level; i++) { // print spasi
            for(int j = 0; j < indentasi[i]; j++){
                printf(" ");
            }
        }
        
        printf("[-%s-]\n", root->kontainer.nama_simpul);
        eKolom *eCol = root->col;
        while(eCol != NULL){
            if (level > 0) { // Kalau bukan root, print indentasi dan garis cabang dulu
                for (int i = 0; i < level; i++) { // print spasi
                    for(int j = 0; j < indentasi[i]; j++){
                        printf(" ");
                    }
                }
            }
            printf(" -%s\n", eCol->kontainer_kol.konsekuensi);
            eCol = eCol->next_kol;
        }
        printf("\n");
        simpul *bantu = root->child; // isi pointer bantu dengan child untuk loop

        if (bantu != NULL) {
            if (bantu->sibling == NULL) {
                /* jika memiliki satu simpul anak */
                printTreePreOrder(bantu, level + 1, indentasi); // rekursif
            } else {
                /* jika memiliki banyak simpul anak */
                /* mencetak simpul anak */
                while (bantu->sibling != root->child) {
                    printTreePreOrder(bantu, level + 1, indentasi);
                    bantu = bantu->sibling;
                }
                /* memproses simpul anak terakhir karena belum terproses dalam pengulangan */
                printTreePreOrder(bantu, level + 1, indentasi); // rekursif
            }
        }
    }
}

// Membuat queue kosong
void createEmpty(queue *Q) {
    Q->first = NULL;
    Q->last = NULL;
}

// Mengecek apakah queue kosong
int isEmpty(queue Q) {
    int hasil = 0;
    if(Q.first == NULL){
        hasil = 1;
    }
    return hasil;
}

int countElement(queue Q) {
    int hasil = 0;

    if (Q.first != NULL) { /* queue tidak kosong */
        elemen *bantu;

        /* inisialisasi */
        bantu = Q.first;

        while (bantu != NULL) {
            /* proses */
            hasil = hasil + 1;

            /* iterasi */
            bantu = bantu->next;
        }
    }

    return hasil;
}

void enqueue(char nama[], queue *Q) {
    elemen *baru;
    baru = (elemen *) malloc(sizeof(elemen));

    // Mengisi data
    strcpy(baru->kontainer.nama, nama);
    baru->next = NULL;

    // Jika queue masih kosong
    if ((*Q).first == NULL) {
        (*Q).first = baru;
    } else {
        // Tambahkan ke akhir queue
        (*Q).last->next = baru;
    }

    // Update pointer last
    (*Q).last = baru;
    baru = NULL;
}

void dequeue(queue *Q) {
    if ((*Q).first != NULL) { /* jika queue bukan queue kosong */
        elemen *hapus = (*Q).first;

        if (countElement(*Q) == 1) {
            // Jika hanya ada satu elemen
            (*Q).first = NULL;
            (*Q).last = NULL;
        } else {
            // Pindah ke elemen berikutnya
            (*Q).first = (*Q).first->next;
            hapus->next = NULL;
        }

        free(hapus);
    }
}


void printQueue(queue Q) {
    if (Q.first != NULL) {

        elemen *bantu = Q.first;
        while (bantu != NULL) {
            printf("-%s\n", bantu->kontainer.nama);
            
            // Iterasi ke elemen berikutnya
            bantu = bantu->next;
        }

    } else {
        // Proses jika queue kosong
        printf("Queue kosong\n");
    }
}