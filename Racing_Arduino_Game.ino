//v.1.0.1 itcooky@mail.ru
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <LCD.h>
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

volatile unsigned long start = 0; 
volatile unsigned long stop = 0; 
unsigned long m = 0; 
unsigned long l = 0;
unsigned long p = 0;
unsigned long s = 0;
unsigned long smax = 0;
int sp = 2; 
int b = 0; 
int c = 0;
int x = 16;
int x2 = 18;
int x3 = 20;
int x4 = 23;
int x12 = 0;
int x13 = 0;
int x14 = 0;
int d = 0;
int t = 250; 
boolean sw = false;
boolean game = false;
int pb = 0;
int addr = 0;
void setup() {
pinMode(sp, INPUT);
digitalWrite(sp, HIGH);
lcd.begin(16,2);
lcd.setCursor(0, 0);
lcd.print(" Racing the Game");
lcd.setCursor(0, 1);
lcd.print(">>Press to start");
}


void loop() {
  
  
  if ((digitalRead(sp) == HIGH) && (game == false))
  {  
p = p + 1;
m = millis();
  }

if ((millis() - m >  40) && (p > 0) && (game == false)) { 
if ( sw == true) {
b = 0;
sw = false;
}
b = b + 1;
p = 0; 

}

if ((millis() - m >  450) && (b > 0) && (sw == false)&& (game == false)) { 
sw = true;
c = b;
lcd.clear();   

if (c == 2)  {
lcd.print("1 press-Start");
lcd.setCursor(0, 1);
lcd.print("3 press-DeletRec");
}
}

if (c == 3)  {
EEPROM.write(addr, 0);
lcd.setCursor(0, 0);
lcd.print("Deleted Record");
lcd.setCursor(0, 1);
lcd.print("   Statistics");
}


if (c == 1 ) {
game = true;

if ((millis() - l >  t)) { 
  
if (((x == 16) && (x2 == 16)) || ((x2 == 16) && (x3 == 16))) {
x2= x2+2;
}
if (((x == 16) && (x4 == 16)) || ((x4 == 16) && (x3 == 16))) {
x4= x4+2;
}

if (pb == 0) {
lcd.setCursor(0, 0);
lcd.print("Z");
lcd.setCursor(0, 1);
lcd.print(" ");
}  
if (pb == 1) {
lcd.setCursor(0, 1);
lcd.print("Z");
lcd.setCursor(0, 0);
lcd.print(" ");
}   

x = x - 1;
lcd.setCursor(x, 0);
lcd.print("BB ");

x2 = x2 - 1;
lcd.setCursor(x2, 1);
lcd.print("BB ");
if (d > 0 ) {
x3 = x3 -1;
lcd.setCursor(x3, 0);
lcd.print("EE ");
}
if (d > 1 ) {
x4 = x4 - 1;
lcd.setCursor(x4, 1);
lcd.print("EE ");
}  

lcd.setCursor(12, 1);
lcd.print(s);
if (((x == 0) && (pb == 0)) || ((x2 == 0) && (pb == 1)) || ((x3 == 0) && (pb == 0)) || ((x4 == 0) && (pb == 1))) {
game = false;  
}
l = millis();
s = s + 1;
//t = t - 1;
switch (s) {
  case 50: 
  t = t - 20;
  break;
  case 100:
  d = d + 1;
  break;
  case 250:
  t = t - 10;
  break;
  case 400:
  d = d + 1;
  break;
  case 500:
  t = t - 10;
  break;
  case 600:
  t = t - 10;
  break;
}

}
if (x == 0) {
x = 16 + random(0,1);
lcd.setCursor(1, 0);
lcd.print(" ");
x12= x + random(2,3)+2;
x13 = x12 + random(1,3)+2;
x14 = x13 + random(2,3)+3;
}
if (x2 == 0) {
x2 = x12;
lcd.setCursor(1, 1);
lcd.print(" ");

}
if (x3 == 0) {
x3 = x13;
lcd.setCursor(1, 0);
lcd.print(" ");


}
if (x4 == 0) {
x4 = x14;
lcd.setCursor(1, 1);
lcd.print(" ");

 
} 
}

if ((digitalRead(sp) == HIGH) && (game == true))
  {  
p = p + 1;
m = millis();
  }

if ((millis() - m > 40) && (p > 0) && (game == true)) { 

if (pb == 0) { 
pb = 1; 
}
else { 
pb = 0;
}
p = 0; 
}

if ((s > 0) && (game == false)) { 
 smax = EEPROM.read(addr);
if (s > smax) {
EEPROM.write(addr, s);
lcd.clear();
lcd.setCursor(0, 0);
l = millis();
lcd.print("!!!NEW RECORD!!!");
lcd.setCursor(0, 1);
lcd.print(" Best Score:");
lcd.setCursor(12, 1);
lcd.print(s);
}
else {
lcd.clear();
lcd.setCursor(0, 0);
l = millis();
lcd.print("###GAME##OVER###");
lcd.setCursor(0, 1);
lcd.print("YScore:");
lcd.setCursor(7, 1);
lcd.print(s);
lcd.setCursor(11, 1);
lcd.print("<");
lcd.setCursor(12, 1);
lcd.print(smax);
}
c = 0;
s = 0;
t = 250;
d = 0;
x = 16;
x2 = 18;
x3 = 20;
x4 = 23;
}
}
void begin() {
	start = millis(); 
}

void end() {
	stop = millis() - start; 
}
