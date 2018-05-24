#include <Servo.h>

const int sasaranKuning[6]  = {22, 23, 24, 25, 26, 27};
const int sasaranMerah[6]   = {28, 29, 30, 31, 32, 33};
const int sasaranHijau[6]   = {2, 3, 4, 5, 6, 7};
const int sasaranBiru[6]    = {8, 9, 10, 11, 12, 13,};
const int mainStart = 50;
const int ends = 49;


bool flagKuning[6] = {false, false, false, false, false, false};
bool flagMerah[6] = {false, false, false, false, false, false};
bool flagHijau[6] = {false, false, false, false, false, false};
bool flagBiru[6] = {false, false, false, false, false, false};

int buttonStateKuning[6];
int buttonStateMerah[6];
int buttonStateHijau[6];
int buttonStateBiru[6];

bool limit;
bool HelloStart = false;

int superStart = false;

int endGame;
Servo myservo;


void setup() {
  myservo.attach(53);
  Serial.begin(9600);
  pinMode(mainStart, INPUT_PULLUP);
  pinMode(ends, INPUT_PULLUP);

  for (int i = 0; i < 6; i++) {
    pinMode(sasaranKuning[i], INPUT_PULLUP);
    pinMode(sasaranMerah[i], INPUT_PULLUP);
    pinMode(sasaranHijau[i], INPUT_PULLUP);
    pinMode(sasaranBiru[i], INPUT_PULLUP);
  }
}

void loop() {
  //state start utama pada pin 50
  if (!HelloStart) {
    superStart = digitalRead(mainStart);
    if (superStart == 0) {
      //Mengirim data start pada sistem unity 3d, dan Menjalankan Servo
      myservo.write(90);
      HelloStart = true;
      Serial.write(100);
      Serial.flush();
      delay(2000);
      myservo.write(0);
      delay(2000);
    }
  }

  else {
    //membaca digital pin 49 untuk inisialisasi game selesai.
    endGame = digitalRead(ends);
    // looping pembacaan sistem tembak dengan 4 sisi (Kuning, Merah, Hijau, Biru)
    for (int i = 0; i < 6; i++) {
      buttonStateKuning[i] = digitalRead(sasaranKuning[i]);
      buttonStateMerah[i] = digitalRead(sasaranMerah[i]);
      buttonStateHijau[i] = digitalRead(sasaranHijau[i]);
      buttonStateBiru[i] = digitalRead(sasaranBiru[i]);

      ///////////////////////////////////////////////////////////////////Kuning
      //membaca Sistem sisi warna Kuning
      if (!flagKuning[i]) {
        if (buttonStateKuning[i] == 0)
        {
          if (i >= 0 && i <= 2 )Serial.write(1);
          if (i >= 3 && i <= 4 )Serial.write(2);
          if (i == 5 )Serial.write(3);
          flagKuning[i] = true;
          Serial.flush();
          delay(1001);
          //Serial.println(i);
        }
      }

      ///////////////////////////////////////////////////////////////////Merah
      //membaca Sistem sisi warna Merah
      if (!flagMerah[i]) {
        if (buttonStateMerah[i] == 0)
        {
          if (i >= 0 && i <= 2 )Serial.write(4);
          if (i >= 3 && i <= 4 )Serial.write(5);
          if (i == 5 )Serial.write(6);
          flagMerah[i] = true;
          Serial.flush();
          delay(1001);
          //Serial.println(i);
        }
      }

      ///////////////////////////////////////////////////////////////////Hijau
      //membaca Sistem sisi warna Hijau
      if (!flagHijau[i]) {
        if (buttonStateHijau[i] == 0)
        {
          if (i >= 0 && i <= 2 )Serial.write(7);
          if (i >= 3 && i <= 4 )Serial.write(8);
          if (i == 5 )Serial.write(9);
          flagHijau[i] = true;
          Serial.flush();
          delay(1001);
          //Serial.println(i);
        }
      }

      ///////////////////////////////////////////////////////////////////Biru
      //membaca Sistem sisi warna Biru
      if (!flagBiru[i]) {
        if (buttonStateBiru[i] == 0)
        {
          if (i >= 0 && i <= 2 )Serial.write(10);
          if (i >= 3 && i <= 4 )Serial.write(11);
          if (i == 5 )Serial.write(12);
          flagBiru[i] = true;
          Serial.flush();
          delay(1001);
          //Serial.println(i);
        }
      }
    }
    //Jika Tombol End game(pin 49), Maka Game Selesai.
    if (endGame == 0) {
      Serial.write(99);
      Serial.flush();
      delay(1001);
      HelloStart = false;
      for (int i = 0; i < 6; i++) {
        flagKuning[i] = false;
        flagMerah[i] = false;
        flagHijau[i] = false;
        flagBiru[i] = false;
      }
    }
  }
}

