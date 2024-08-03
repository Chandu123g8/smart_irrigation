#include<LiquidCrystal.h>


#define echo 9
#define trigger 10
#define tank_pump 4

#define moisture_sensor A0
#define tempPin A1
long duration;
int distance;
int moisture_value;
int distance_percent;
int moist_percent;
float temp;
LiquidCrystal lcd(12,11,8,7,6,5);


void setup1()
{
  pinMode(tempPin, INPUT);
  Serial.begin(9600);
}

void loop1() 
{
temp = analogRead(tempPin);
temp = (temp *5.0*100.0)/1024.0; 
Serial.println(temp);
delay(100);
}



//LCD DISPLAY
void setup () 
{
lcd.begin(20,4);
Serial.begin(9600);
pinMode(echo,INPUT);
pinMode(moisture_sensor,INPUT);
pinMode(trigger,OUTPUT);
digitalWrite(trigger,LOW);

pinMode(tank_pump,OUTPUT);

digitalWrite(tank_pump,LOW);
lcd.setCursor(0,0);
lcd.print("WELCOME");
lcd.setCursor(0,1);
lcd.print("AUTOMATED IRRIGATION");
lcd.setCursor(0,2);
lcd.print("SYSTEM"); 
delay(100);
lcd.clear();
}



// WATER LEVEL SENSOR.
void loop()
{
digitalWrite(trigger,LOW);
delayMicroseconds(2);
digitalWrite(trigger,HIGH);
delayMicroseconds(10); 
digitalWrite(trigger,LOW);
duration=pulseIn(echo,HIGH);
distance=duration*0.017; 
distance_percent=map( distance,0,1023,0,100);
moisture_value= analogRead(moisture_sensor);
moist_percent=map(moisture_value,0,1023,0,100);
condition();
loop1();
}


//MAIN WORKING
void condition()
{
if (distance_percent>50 && moist_percent>50)
{
LCD_3();
digitalWrite(tank_pump,LOW);

delay(100);
}

else if (distance_percent<50 &&moist_percent<50)
{
LCD_2();
digitalWrite(tank_pump,HIGH);

delay(100);
}

else if (distance_percent>50 &&moist_percent<50)
{
LCD_4();
digitalWrite(tank_pump,LOW);

delay(100);
}

else if (distance_percent<50 &&moist_percent>50)
{
LCD_1();
digitalWrite(tank_pump,HIGH);

delay(100);
}
}


//DIFFRENT LCD DISPLAY FUNCTIONS
void LCD_1()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");

lcd.setCursor(0,2);
lcd.print("TANK PUMP:");
lcd.print("ON");
}

void LCD_2()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");

lcd.setCursor(0,2);
lcd.print("TANK PUMP:");
lcd.print("ON");
}
  
void LCD_3()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("TANK PUMP:");
lcd.print("OFF");
}

void LCD_4()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TANK LEVEL= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("MOISTURE STATUS= ");
lcd.print(moist_percent);
lcd.print("%");

lcd.setCursor(0,2);
lcd.print("TANK PUMP:");
lcd.print("OFF");
}
