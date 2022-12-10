#include <TimerOne.h>

//Peripherals to use
//Outputs
int PWMPin = 5;
int IN1 = 8;
int IN2 = 6;
//Inputs
int CanalA = 2;
int CanalB = 3;

//Variables
int count;
int u;
double y;
double y1;
double yf;
double yf1;
double theta;
double t;
double a;
double b;
double c;
double Kp = 4;
double Td = 0;
double Ti = 10000000;
double m, m1;  Timer1.initialize(10000);

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
  Timer1.attachInterrupt(callback);
  a = Kp * (1 + (ts / Ti) + (Td/ts));
  b = Kp*(-1-2*(Td/ts));
  c = Kp*(Td/ts);
  count = 0;
}

void callback() {
  t = ts + t;

  y = theta;
  e = u - yf;
  m = m1 +(a*e)+(b*e1)+(c*e2);
  m1 = m;
  e2 = e1;
  e1 = e;
  yf = 0.1813*y1 + 0.8187*yf1;
  y1 = y;
  yf1 = yf;
}


void loop() {
  attachInterrupt(digitalPinToInterrupt(CanalA), interrupcion1, RISING);
  
  if (t < 3) {
    u = 0;
  }
  else {
    u = 90;
  }

   if (m > 0){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      if (m > 255){
        m = 255;
      } 
   } 
    else if (m <= 0){
       digitalWrite(IN1, HIGH);
       digitalWrite(IN2, LOW);
       if (m < -255){
         m = -255;
       } 
       m = -1 * m; 
    }

  analogWrite(PWMPin, m);
 
  Serial.print(y);
  Serial.print("\t");
  Serial.print(u);
  Serial.print("\t");
  Serial.println(m);
  
}

void interrupcion1(){
  if(digitalRead(CanalB)){
  count ++;
  }
  else{
    count --;
    }
  theta = count*(0.677966);
 }
