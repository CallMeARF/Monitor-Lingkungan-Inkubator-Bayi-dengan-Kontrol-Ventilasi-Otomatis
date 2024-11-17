# Monitor Lingkungan Inkubator Bayi dengan Kontrol Ventilasi Otomatis

## Dibuat oleh: Kelompok 2 IoT - IF-VA

**Anggota Kelompok**:

1. RIFAN WAROSY SIROJUDIN (220660121033)
2. ALIP RIZKY FIRDAUS (220660121078)
3. M ARIF FIRMANSYAH (220660121013)
4. NAUFAL SIDDIQ RAMADHAN (220660121035)
5. RIVAL FAKHRI AMRULLAH (220660121134)

## Deskripsi Proyek

Proyek ini bertujuan untuk menciptakan sistem otomatis yang dapat memantau dan mengontrol kondisi lingkungan dalam inkubator bayi. Dengan menggunakan sensor dan aktuator, sistem ini menjaga suhu, kelembapan, dan kualitas udara agar tetap dalam batas yang aman. Data juga dapat dipantau secara real-time melalui aplikasi Blynk.

## Fitur Utama

- **Monitoring Suhu & Kelembapan:** Menggunakan sensor DHT22.
- **Monitoring Kualitas Udara:** Menggunakan sensor MQ-135.
- **Kontrol Ventilasi Otomatis:** Servo motor akan membuka atau menutup ventilasi sesuai dengan data dari sensor.
- **Pemantauan Jarak Jauh:** Data ditampilkan secara real-time melalui aplikasi Blynk.

## Instalasi

1. Clone repository ini

2. Pastikan Anda sudah menginstal Arduino IDE dan pustaka berikut:

   - **Blynk**
   - **DHT Sensor Library**
   - **Servo Library**

3. Konfigurasikan kredensial Wi-Fi dan Token Blynk Anda di kode.

4. Upload kode ke ESP8266/NodeMCU.

## Cara Kerja

1. **Monitoring:** Sensor DHT22 dan MQ-135 mengukur suhu, kelembapan, dan kualitas udara secara terus-menerus.
2. **Kontrol Ventilasi:** Jika data sensor melebihi ambang batas, servo motor akan bergerak untuk membuka atau menutup ventilasi.
3. **Pemantauan Jarak Jauh:** Data dikirimkan ke aplikasi Blynk untuk dipantau melalui smartphone.
