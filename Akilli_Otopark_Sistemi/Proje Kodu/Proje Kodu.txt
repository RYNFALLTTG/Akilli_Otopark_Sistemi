#include <Servo.h>
#include <PCD8544.h>
Servo myservo; 
 PCD8544 lcd;
 int button=2;
int BUTTON=29;
float sonuc;
int sonuclanma;
int button_ort=29;
float sum=0;
bool durum=true;
int g=0;
/////////////////////////////////////////////
int inputPin = 29;
float okuma[10];



#define SENSOR_PIN 30
#define BUZZER_PIN 13
#define RELAY_PIN 8
#define SPRINKLER_START_DELAY 5000  
#define SPRINKLER_ON_TIME 3000     
int pos = 0;

float deger;
float toplam=0;
int i;
int zort;

/////////////////////////////
const int trigPin = 36;
const int echoPin = 10;
const int level4 = 13;
const int level3 = 11;
const int level2 = 12;
const int level1 = 46;
const int level5 = 32;
 

long duration;
int distance;
int safetyDistance;

unsigned long previousTime = millis();
 
void setup() {

  

 pinMode(29,INPUT);
  
  lcd.begin(84, 48);
myservo.attach(9);
myservo.write(0);
delay (5000);
pinMode(button,INPUT);
 pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600); 
deger=analogRead(10);   
pinMode(trigPin,OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(level4, OUTPUT);
pinMode(level3, OUTPUT);
pinMode(level2, OUTPUT);
pinMode(level1, OUTPUT);
pinMode(level5, OUTPUT);
pinMode(29,OUTPUT);
}

void loop() {
  
  unsigned long previousTime = millis();
  
  int sensorValue = digitalRead(SENSOR_PIN);

  //There is fire
  if (sensorValue == LOW)
  {

    if (millis() - previousTime > SPRINKLER_START_DELAY)  //We will wait for few seconds before sprinkler can be started once fire is detected.
    {
    digitalWrite(RELAY_PIN,LOW);
    Serial.println("PEACE");
    digitalWrite(BUZZER_PIN,LOW);


    }
  }
  else
  {
       
      digitalWrite(RELAY_PIN,HIGH);                       //Relay is low level triggered relay so we need to write LOW to switch on the light 
      delay(SPRINKLER_ON_TIME);                           //Keep sprinkler on for sometime.
      Serial.println("FIRE FIRE");
      lcd.setCursor(4, 3);
      lcd.print("FIRE FIRE");
      myservo.write(90);
      
      digitalWrite(BUZZER_PIN,HIGH);
  }
      if(sensorValue == LOW){
     digitalWrite(RELAY_PIN,LOW);                       //Relay is low level triggered relay so we need to write LOW to switch on the light        
      digitalWrite(BUZZER_PIN,LOW);
      lcd.clear();
      myservo.write(0);

      }

    previousTime = 0;

  if(digitalRead(2)==1){
    myservo.write(90);
    delay(2000);
    myservo.write(0);
  }


////////////////////////////////////

zort= 0.0;
for (int i=0; i<10; i++)
{
float deger =digitalRead (29);
okuma[i]= 5;
Serial.println (zort);
//////////////////////////////

 if(digitalRead(29)==1){
   durum=false;
   Serial.println("basildi");
   lcd.setCursor(0, 4);
  lcd.print("Ort aliniyor");
 }
 if(durum==false){
   
  sum = (sum +(distance));
 
 if(g==10){
  sonuclanma=sum/10;
 Serial.print("ort_sonucu :");
 Serial.println(sonuclanma);
 lcd.setCursor(0, 0);
 lcd.print("ort_sonucu :");
  lcd.setCursor(3, 5);
 lcd.print(sonuclanma);
 delay(3000);

 sum=0;
 g=-1;
 durum=true;
 }
g=g+1;
}
///////////////////////////////////





 

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
 
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
 
// Calculating the distance
distance= duration*0.034/2;
 
safetyDistance = distance;


if (distance <=9)
{
  digitalWrite(level3, HIGH);

 

}


else
{
  
  digitalWrite(level3, LOW);
  
}



if (distance <=18)
{
  digitalWrite(level2, HIGH);
 
}




else
{
  digitalWrite(level2, LOW);
}



if (distance <=4)
{
  digitalWrite(level1, HIGH);

}



else
{
  digitalWrite(level1, LOW);
}





// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

 lcd.setCursor(0, 0);

  lcd.println(distance);
  delay(700);
  lcd.setCursor(0, 0);
  lcd.clear();
  } 
 }
  
 
 
