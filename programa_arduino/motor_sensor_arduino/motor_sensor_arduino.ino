#include<Stepper.h>
#include<Ultrasonic.h>

int echoPinx = 12;
int trigPinx = 11;

int echoPiny = 13;
int trigPiny = 10;

Ultrasonic ultrassomx(trigPinx, echoPinx);
Ultrasonic ultrassomy(trigPiny, echoPiny);

int P1 = 9;
int P2 = 8;
int P3 = 7;
int P4 = 6;

int P5 = 5;
int P6 = 4;
int P7 = 3;
int P8 = 2;

bool L;
double Sx;
double Sy;
long durationx;
long durationy;

void setup() {
  Serial.begin(9600);
  pinMode(trigPinx, OUTPUT);
  pinMode(echoPinx, INPUT);
  pinMode(trigPiny, OUTPUT);
  pinMode(echoPiny, INPUT);

  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P8, OUTPUT);

}


void loop() {
 int P[] = {-30+30,-120+120};
  L = 1;

  digitalWrite(trigPinx, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinx, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinx, LOW);

  durationx = pulseIn(echoPinx, HIGH);
  Sx = microsecondsToCentimetersx(durationx);

  Serial.print("DistanciaX = ");
  Serial.print(Sx);
  Serial.print(" cm\n");
  Serial.println();

  digitalWrite(trigPiny, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPiny, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPiny, LOW);

  durationy = pulseIn(echoPiny, HIGH);
  Sy = microsecondsToCentimetersy(durationy);

  Serial.print("DistanciaY = ");
  Serial.print(Sy);
  Serial.print(" cm\n");
  Serial.println();

  if(L > 0){
    double Dx = P[0];
    double Dy = P[1] ;
    bool mx = 0;
    bool my = 0;

    if(Dx > 0){
      mx = 1;
      my = 0;
      while(Sx < Dx && mx == 1 && my == 0){
        avancar();
        Sx += Sx;
        Dy = -1;
      }
    } else if( Dx <= 0){
      mx = 1;
      my = 0;
      while( Sx > abs(Dx) && Sx != 4.0 && mx == 1 && my == 0) {
        regredir();
          Sx -= Sx;
          Dy = -1 ;
      } 
    }

    if(Dy < 0){
      mx = 0;
      my = 1;
    while( Sy < abs(Dy) && mx == 0 && my == 1){
      decer();
      Sy += Sy;
      Dx = -1;
      }
    }else if(Dy >= 0){
      mx = 0;
      my = 1;
      while (Sy > abs(Dy) && Sy != 4 && mx == 0 && my == 1){
        subir();
        Sy -= Sy;
        Dx = -1;
      }
    }
  }
}

long microsecondsToCentimetersx(long microseconds){
  return ultrassomx.Ranging(microseconds);
}
long microsecondsToCentimetersy(long microseconds){
  return ultrassomy.Ranging(microseconds);
}

void parada(){
  digitalWrite(P1, 0);
  digitalWrite(P2, 0);
  digitalWrite(P3, 0);
  digitalWrite(P4, 0);
  digitalWrite(P5, 0);
  digitalWrite(P6, 0);
  digitalWrite(P7, 0);
  digitalWrite(P8, 0);
  
}

void avancar(){
  primeirox();
  delay(20);
  segundox();
  delay(20);
  terceirox();
  delay(20);
  quartox();
  delay(20);
}

void regredir(){
  quartox();
  delay(20);
  terceirox();
  delay(20);
  segundox();
  delay(20);
  primeirox();
  delay(20);
}
void decer(){
  quartoy();
  delay(20);
  terceiroy();
  delay(20);
  segundoy();
  delay(20);
  primeiroy();
  delay(20);
}

void subir(){
  primeiroy();
  delay(20);
  segundoy();
  delay(20);
  terceiroy();
  delay(20);
  quartoy();
  delay(20);
}

void primeirox(){
  digitalWrite(P1, 1);
  digitalWrite(P2, 0);
  digitalWrite(P3, 0);
  digitalWrite(P4, 0);
}
void segundox(){
  digitalWrite(P1, 0);
  digitalWrite(P2, 1);
  digitalWrite(P3, 0);
  digitalWrite(P4, 0);
}
void terceirox(){
  digitalWrite(P1, 0);
  digitalWrite(P2, 0);
  digitalWrite(P3, 1);
  digitalWrite(P4, 0);
}
void quartox(){
  digitalWrite(P1, 0);
  digitalWrite(P2, 0);
  digitalWrite(P3, 0);
  digitalWrite(P4, 1);
}

void primeiroy(){
  digitalWrite(P5, 1);
  digitalWrite(P6, 0);
  digitalWrite(P7, 0);
  digitalWrite(P8, 0);
}
void segundoy(){
  digitalWrite(P5, 0);
  digitalWrite(P6, 1);
  digitalWrite(P7, 0);
  digitalWrite(P8, 0);
}
void terceiroy(){
  digitalWrite(P5, 0);
  digitalWrite(P6, 0);
  digitalWrite(P7, 1);
  digitalWrite(P8, 0);
}
void quartoy(){
  digitalWrite(P5, 0);
  digitalWrite(P6, 0);
  digitalWrite(P7, 0);
  digitalWrite(P8, 1);
}

