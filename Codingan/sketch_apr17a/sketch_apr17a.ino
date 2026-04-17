#include <Servo.h>

// =======================
// PIN ULTRASONIC
// =======================
#define trigPin 2
#define echoPin 3

// =======================
// PIN MOTOR L298N
// =======================
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

// =======================
Servo myServo;

// =======================
// SPEED SETTING (BISA KAMU UBAH)
// =======================
int speedMaju   = 220;
int speedBelok  = 200;
int speedMundur = 180;

int batasJarak = 20; // cm

// =======================
// FUNCTION BACA JARAK
// =======================
int bacaJarak() {
  int total = 0;

  for (int i = 0; i < 5; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long durasi = pulseIn(echoPin, HIGH, 20000);
    int jarak = durasi * 0.034 / 2;

    if (jarak == 0) jarak = 200;

    total += jarak;
    delay(5);
  }

  return total / 5;
}

// =======================
// GERAK MOTOR
// =======================
void maju() {
  analogWrite(ENA, speedMaju);
  analogWrite(ENB, speedMaju);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  analogWrite(ENA, speedMundur);
  analogWrite(ENB, speedMundur);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  analogWrite(ENA, speedBelok);
  analogWrite(ENB, speedBelok);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void belokKanan() {
  analogWrite(ENA, speedBelok);
  analogWrite(ENB, speedBelok);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// =======================
// SETUP
// =======================
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);

  myServo.attach(4);
  myServo.write(90);
  delay(500);
}

// =======================
// LOOP
// =======================
void loop() {

  int depan = bacaJarak();
  Serial.print("Depan: ");
  Serial.println(depan);

  if (depan > batasJarak) {
    maju();
  } 
  else {
    stopMotor();
    delay(200);

    mundur();
    delay(300);
    stopMotor();
    delay(200);

    // CEK KANAN
    myServo.write(30);
    delay(300);
    int kanan = bacaJarak();

    Serial.print("Kanan: ");
    Serial.println(kanan);

    // CEK KIRI
    myServo.write(150);
    delay(300);
    int kiri = bacaJarak();

    Serial.print("Kiri: ");
    Serial.println(kiri);

    // Tengah lagi
    myServo.write(90);
    delay(200);

    if (kanan > kiri) {
      belokKanan();
      delay(400);
    } else {
      belokKiri();
      delay(400);
    }

    stopMotor();
  }
}

codingan robot kedua