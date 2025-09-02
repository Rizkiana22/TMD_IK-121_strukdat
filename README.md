# TMD Project – Struktur Data dan Algoritma

## Deskripsi
Program ini dibuat sebagai bagian dari tugas mata kuliah **Struktur Data dan Algoritma**.  
Penulis: **Muhammad Rizkiana Pratama (NIM 2404421)**.  

Program mengimplementasikan struktur data **tree** dengan fitur tambahan berupa pencatatan **konsekuensi** di setiap simpul. Program menerima input berupa daftar simpul beserta induknya, kemudian membangun tree menggunakan algoritma DFS. Setelah itu, program dapat menampilkan tree, memangkas tree berdasarkan jalur ke simpul target (*pruning*), dan menampilkan daftar konsekuensi yang terkait.

---

## Fitur Program
- **Membuat tree** dari input sejumlah simpul.
- **Menambahkan anak simpul** ke simpul induk tertentu.
- **Menambahkan konsekuensi** ke setiap simpul.
- **Menghitung indentasi** untuk keperluan pencetakan tree.
- **Mencetak tree** dengan format terindentasi (PreOrder).
- **Mencari jalur ke simpul target** dan melakukan **pruning** sehingga hanya tersisa jalur menuju simpul target.
- **Menampilkan konsekuensi** dari simpul target.

---

## Analisis Kompleksitas (Big-O)
1. **Input simpul sebanyak `n` dengan `m` konsekuensi**  
   - Menggunakan `findSimpul` (DFS) untuk mencari posisi penambahan simpul → kasus terburuk `O(n)`.  
   - Karena ada `n` simpul, total kompleksitas input adalah **O(n² + m)**.  

2. **Hitung indentasi**  
   - Kompleksitas **O(n + m)** (simpul + konsekuensi).  

3. **Print tree**  
   - Kompleksitas **O(n + m)**.  

4. **Pruning**  
   - Menggunakan DFS → kompleksitas **O(n)**.  

5. **Print konsekuensi**  
   - Kompleksitas **O(m)**.  

📌 **Kesimpulan**: Total kompleksitas program adalah **O(n² + m)**.  

---

## Cara Kompilasi & Menjalankan
Gunakan GCC:
```bash
gcc main.c mesin.c -o tmd.exe
./tmd.exe
