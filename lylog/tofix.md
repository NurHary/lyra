# To Fix Lylog
ketika banyak file c memanggil Header, maka akan terjadi bentrokan
luar biasa, sehingga harus mencari cara untuk menghindari bentrokan
tersebut


## Apa saja yang bentrokan
collect2: error: ld returned 1 exit status

1. fungsi "___print_log" banyak
2. lylogConf... juga banyak
3. LYGC_LOGMSG dan LYGC_LOGCOLORS


jadi pertanyaannya adalah bagaimana caranya bisa membuat banyak LYGC_LOGMSG dan LYGC_LOGCOLORS ketika kita mau melakukann pemanggilan
lylog header ke beragam files


Sekarang bagaimana caranya menambahkan Header Enum pada satu titik saja
