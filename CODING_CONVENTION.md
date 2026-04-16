# LYRA CODING STANDARD / CONVENTION
Standard pemograman ini berlaku untuk semua proyek Lyra beserta untuk semua kodingan personal proyek Killing Whales.

## Coding Convention
1. Fungsi (Umum) ditulis dengan model lower snake_case dengan 2 prefix diawal berupa lowercase ly serta tambahan sampai 4 dengan mengikuti konteks file tersebut (contoh: lymath_add_v2, lyutil_convert_color)
2. Struct ditulis dengan model upper CamelCase dimana memiliki 2 prefix diawal dengan bentuk CamelCase juga (contoh: Ly_LinkedList)
3. Enum ditulis dengan SCREAMING_SNAKE_CASE dengan prefix tambahan "LYE_" (contoh: LYE_LOG_COLOR)
4. Usable Macro ditulis dengan full uppercase dengan prefix "LYM_" (contoh: LYM_ENABLESIMD)
5. Global Const Variable ditulis dengan SCREAMING_SNAKE_CASE dengan prefix "LYG_"
6. Global Mutable Variable ditulis dengan SCREAMING_SNAKE_CASE dengan prefix "LYGM_"
7. Semua operasi yang dilakukan pada Struct memiliki aturan penulisan mengikuti yang diatas tapi dengan tambahan postfix yang menunjuk konteks tersebut (contoh: LYM_INITDEFAULT_LINKEDLIST, ly_access_bit_bpb)

## Rules Of Code
1. Minimalisir penggunaan complex flow, bahkan kalau bisa hindari (recursion, goto, setjmp, dan lainnya)
2. Selalu buat Max bound untuk loop apapun
3. File Prolog: Sangat penting untuk ada, File Prolog setidaknya mengandung: nama files, tujuan, notes, error / warn msg, asumsi dan batasan, dan algoritma. Jauh lebih baik lagi apabila ada dependency, file ref, external var, external ref
4. Function Documentation: pastikan selalu ada documentation untuk setiap fungsi diatas dengan kriteria: kegunaan dan notes. Apabila bisa sertakan parameter serta variable yang dibutuhkan dalam fungsi tersebut
5. Code Documentation: usahakan untuk menggunakan inline tabbed comment untuk menjelaskan apa yang dilakukan codes. Dan gunakan enter documentation untuk notes pengembangan
6. Fungsi tidak boleh lebih panjang dari 60 lines

Single file Library Rules
1.
2.

## Single Header Library Rules
1. Tulis itu di C murni
2. Dalam headernya, jangan pernah mengotori global scope nya dengan fungsi yang tidak berguna / internal
3. Harus simple; apabila tidak simple make jadikan itu single file library
4. Usahakan tidak menggunakan malloc; tujuan supaya pengguna tidak perlu repot memanage memoryRules For Stables Release
1. Sebelum rilis, pastikan tidak ada satupun warning dan bahkan kalau bisa selalu aktifkan -Werror
