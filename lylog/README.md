# Lylog
Single Header Library Modules for Lyra Logging Systems

## Cara Menggunakan
Copy saja header filenya, lalu include dimanapun, pastikan ada satu include dengan implementasinya `___LYLOG_IMPLEMENTATION___`

lylog menyediakan 4 default messages, yaitu:
1. `ERROR`
2. `WARN`
3. `INFO`
4. `FATAL`

Contoh Penggunaan
`lym_printlog(INFO, "INIT VARIABLES ; Values: %d", 5) // tidak usah ditambahkan "\n"`
`lym_printlog(WARN, "SYSTEMS TIDAK HARUSNYA BERJALAN DEMIKIAN") // tidak usah ditambahkan "\n"`

## Config
ada beberapa konfigurasi yang telah disediakan oleh lylog dengan memanggil fungsi saja,
konfigurasi tersebut ialah sebagai berikut:
1. Menampilkan Files
2. hanya menapilkan texts saja
3. menampilkan berdasarkan level saja (tampilkan 2, maka x >= 2 akan ditampilkan)

Fungsi yang berkorespondensi dengan yang diatas
1. `void lylogConfToggleFileInfo();`
2. `void lylogConfToggleTxtOnly();`
3. `void lylogConfLSetLevel(i32 msge);`

adapun untuk konfigurasi yang lainnya seperti konfigurasi warna ataupun messages untuk saat ini
masih di nonaktifkan dan akan di tambahkan di update selanjutnya. untuk saat ini apabila ingin menambahkan
warna dan messages sendiri, buka dan edit header files, lalu cari `#define LYMC_LOGDEFAULT(X).....` lalu tambahkan
nama dan warna mengikuti contoh tersebut


## Target Berikutnya
1. _FEATURES_: Sistem untuk menambahkan Messages dan Color Customs
2. _REFACTOR_: Memperbaiki Runtutan Sistem
3. _CHANGE_: Mengubah warna messages defaultnya menjadi warna yang lebih cocok
4. _FEATURES_: Menambahkan config untuk menambahkan line dan disable waktu
