# ASCII Maze Runner : Endless Level Maze Game in C
- [Deskripsi](#deskripsi)
- [Fitur Utama](#fitur-utama)
- [Cara Instalasi](#cara-instalasi)
  - [Quick Run](#quick-run)
  - [Development](#development)
- [Cara Bermain](#cara-bermain)
- [Screenshot Aplikasi](#screenshot-aplikasi)

## Deskripsi
"ASCII Maze Runner" merupakan game sederhana berupa endless level maze yang menantang pemain untuk mencari jalan keluar dari labirin sambil menghindari monster yang tersembunyi. Setiap level dalam permainan ini menawarkan labirin yang unik dengan bentuk dan posisi monster yang selalu teracak sehingga memberikan tantangan yang terus-menerus kepada pemain.

## Fitur Utama
- Labirin tak berujung yang dihasilkan secara acak setiap kali program dijalankan.
- Terdapat monster tersembunyi di dalam labirin yang harus dihindari.
- Pemain dapat bergerak ke atas, ke bawah, ke kiri, dan ke kanan.
- Sistem scoreboard dan highscore.
- Tampilan berwarna.

## Cara Instalasi
### Quick Run
#### Dependencies:
- Download executable file (ASCII-Maze-Runner-v1.1.0.zip) [di sini](https://github.com/mbsaloka/ASCII-Maze-Runner/releases/tag/v1.1.0).
- Karena program memanfaatkan ANSI escape sequences untuk mendukung tampilan, aktifkan ANSI escape sequences terlebih dahulu dengan cara mengetikkan perintah berikut ini di CMD.
  ```
  reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
  ```
  Sebagai informasi tambahan, ketikkan perintah berikut di CMD untuk menonaktifkan ANSI escape sequences.
  ```
  reg delete HKCU\Console /v VirtualTerminalLevel /f
  ```
  - Tampilan sebelum ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/a924aa7f-ba07-45e8-95d2-82da41229d2a)
  - Tampilan setelah ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/9a700afe-7bf3-4ccf-b7c6-6fc60b855dae)

#### Instalasi:
- Ekstrak file .zip yang sebelumnya didownload.
- Jalankan file ```ASCII-Maze-Runner.exe```. Jika ada peringatan "Windows protected your PC", klik ```More info``` kemudian ```Run anyway```.

### Development
#### Dependencies:
- [Clone source code](https://github.com/mbsaloka/ASCII-Maze-Runner.git).
- Pastikan compiler C (seperti GCC) sudah terinstal di sistem Anda.
- Karena program memanfaatkan ANSI escape sequences untuk mendukung tampilan, aktifkan ANSI escape sequences terlebih dahulu dengan cara mengetikkan perintah berikut ini di CMD.
  ```
  reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
  ```
  Sebagai informasi tambahan, ketikkan perintah berikut di CMD untuk menonaktifkan ANSI escape sequences.
  ```
  reg delete HKCU\Console /v VirtualTerminalLevel /f
  ```
  - Tampilan sebelum ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/1b626591-5beb-4684-aeac-5470b578bc12)
  - Tampilan setelah ANSI escape sequences diaktifkan:  
    ![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/dc65f973-9a02-4307-95fe-d7404b8dc242)

#### Instalasi:
- Ekstrak file .zip yang sebelumnya didownload.
- Buka folder yang sudah diekstrak kemudian jalankan file ```ASCII-Maze-Runner.c``` di C/C++ IDE. Compile file ```ASCII-Maze-Runner.c``` untuk mendapatkan file ```ASCII-Maze-Runner.exe```.
- Untuk melakukan compile juga bisa dilakukan di CMD dengan cara membuka CMD di direktori tempat file ```ASCII-Maze-Runner.c``` disimpan kemudian ketik ```gcc ASCII-Maze-Runner.c -o ASCII-Maze-Runner```.
- Jalankan file ```ASCII-Maze-Runner.exe```.


## Cara Bermain
1. Jalankan file ```ASCII-Maze-Runner.exe```.
2. Di menu utama, pilih ```START GAME``` untuk memulai game atau pilih ```Lihat Scoreboard``` untuk menampilkan scoreboard.
3. Gunakan arrow atas dan bawah serta ```Enter``` pada keyboard untuk menentukan pilihan.
4. Untuk menggerakkan karakter dalam game, gunakan tombol ```WASD``` untuk bergerak ke atas, kiri, bawah, dan kanan.
5. Di bagian bawah, terdapat indikator banyak monster yang berada di radius 1 petak di sekitar player.
6. ```>``` adalah karakter milik player.
7. ```#``` adalah dinding labirin yang tidak dapat dilalui.
8. ```?``` adalah area yang bisa dilewati. Namun hati-hati, karena bisa saja petak tersebut aman, tetapi bisa saja terdapat monster yang bersembunyi.
9. ```*``` adalah monster yang akan bersembunyi di sepanjang labirin.
10. ```.``` adalah area yang sudah dilewati dan aman.
11. ```N``` adalah jalan keluar untuk menuju ke level selanjutnya
12. Tekan ```Esc``` untuk kembali ke halaman sebelumnya.
13. Tekan ```1``` untuk mengaktifkan cheat.
14. Selesaikan tiap level labirin dan hindarilah monster-monster yang bersembunyi.
15. Teruslah bergerak dan lihat seberapa lama Anda bisa bertahan!

## Screenshot Aplikasi
### Menu Utama
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/e2f43cca-3cdc-43f0-b69a-4c6e0ef18bb3)

### In Game
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/b96aa7e3-1c04-44be-90f3-f06c491907e3)
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/ddb6d123-c54c-4ed2-8c13-0a0f50dd0605)
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/958a3f2c-eee7-4db0-a70c-8c00e969a342)
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/6ed61c10-bee5-46bf-a7ca-a6d47a2fb4fa)

### Game Over
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/32432784-211b-43fa-b6b8-e4757e3d3bd5)
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/0cd19946-1584-4920-b10a-05e21b52c548)

### Cheat Aktif
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/d7aa241d-22a8-410c-8cc8-09d32945d6d7)
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/6314606b-0e40-4a55-af91-0d0bb0239cf0)

### Pilih Warna Karakter
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/4cf017cb-8d36-4963-b589-c96a8cb6e311)

### Scoreboard
![image](https://github.com/mbsaloka/ASCII-Maze-Runner/assets/110384828/7df55589-f041-4273-8846-76c5bb81dc69)

## Pengembang
Proyek ini dikembangkan oleh:  
[Buyung Saloka](https://instagram.com/mbsaloka)
