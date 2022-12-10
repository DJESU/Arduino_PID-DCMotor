#include <TimerOne.h>

//Peripherals to use
//Outputs
int PWMPin = 5;
int IN1 = 8;
int IN2 = 6;
//entradas
int CanalA = 2;
int CanalB = 3;

//Variables
int count;
int u;
int rpm;
int y;
int y1;
double t;
double a;
double b;
double c;
double Kp = 1;
double Td = 0;
double Ti = 10000;
double m, m1;
double e, e1, e2;

//Constants
double ts = .01;

void setup() {
  Serial.begin(9600);
  pinMode(PWMPin, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(CanalA, INPUT);
  pinMode(CanalB, INPUT);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(callback);
  a = Kp * (1 + (ts / Ti) + (Td/ts));
  b = Kp*(-1-2*(Td/ts));
  c = Kp*(Td/ts);
  count = 0;
}

void callback() {
  //Calculate motor actual velocity
  rpm = 60 * (count / (531 * .01));
  y = rpm;

  //Calcular el tiempo
  t = ts + t;

  //Error
  e = u - y;

  //Formula
  m = m1 +(a*e)+(b*e1)+(c*e2);
  m1 = m;
  e2 = e1;
  e1 = e;

/*
  yf = 0.1813*y1 + 0.8187*yf1;
  y1 = y;
  yf1 = yf;
*/
  count = 0;
}


void loop() {
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  attachInterrupt(digitalPinToInterrupt(CanalA), interrupcion1, RISING);
  

  if (m > 255){
    m = 255;
  }
  if (m < 0){
    m = 0;
  }
  
  analogWrite(PWMPin, m);

  Serial.print(t);
  Serial.print("\t");
  Serial.print(y);
  //Serial.print("\t");
  //Serial.print(yf);
  //Serial.print("\t");
  //Serial.println(y);
  
  //Serial.println(count);
}

void interrupcion1()
{
  count ++;
}
