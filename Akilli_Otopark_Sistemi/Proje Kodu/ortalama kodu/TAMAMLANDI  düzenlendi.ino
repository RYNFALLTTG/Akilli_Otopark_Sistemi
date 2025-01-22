#include <Servo.h>
#include <PCD8544.h>

#define SENSOR_PIN 30
#define BUZZER_PIN 13
#define RELAY_PIN 8
#define SPRINKLER_START_DELAY 5000  
#define SPRINKLER_ON_TIME 3000    

int i;
int button=2;
int pos = 0;
int distance;
int safetyDistance;

const int trigPin = 36;
const int echoPin = 10;
const int level4 = 34;
const int level3 = 11;
const int level2 = 12;
const int level1 = 13;
const int level5 = 32;
 
float sonuc; 
float deger;
float toplam=0; 

long duration;
unsigned long previousTime = millis();

Servo myservo; 
PCD8544 lcd;
////////////////////////////////////////////////////////////// 
void setup() {
  
lcd.begin(84, 48);
myservo.attach(9);
myservo.write(0);
delay (5000);
pinMode(RELAY_PIN, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);
pinMode(SENSOR_PIN, INPUT);
pinMode(button,INPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(level4, OUTPUT);
pinMode(level3, OUTPUT);
pinMode(level2, OUTPUT);
pinMode(level1, OUTPUT);
pinMode(level5, OUTPUT);

Serial.begin(9600); 
deger=analogRead(10);  

}
//////////////////////////////////////////////////////////////
void loop() {
  
  unsigned long previousTime = millis();
  
  int sensorValue = digitalRead(SENSOR_PIN);

  if (sensorValue == LOW)
  {
    if (millis() - previousTime > SPRINKLER_START_DELAY){
    digitalWrite(RELAY_PIN,LOW);
    Serial.println("PEACE");
    digitalWrite(BUZZER_PIN,LOW);
    } }

  else
  {
      digitalWrite(RELAY_PIN,HIGH);                       
      delay(SPRINKLER_ON_TIME);                          
      Serial.println("FIRE FIRE");
      lcd.setCursor(0, 0);
      lcd.print("FIRE FIRE");
      myservo.write(90);
      digitalWrite(BUZZER_PIN,HIGH);
  }
    if(sensorValue == LOW){
     digitalWrite(RELAY_PIN,LOW);                          
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

if(button==1){

for(i=0;i<11;i++){
                                  // bu kısıma belki bir ölçüm kodu gerekebilir.
  toplam=toplam+deger;          // delay süresi ölçüm alma aralığı
  delay(1000);
if(i=10){
  sonuc=(toplam/10);                      // 10 ve 11 degeri istege göre değiştirilecek.
  lcd.setCursor(0, 0);
  lcd.print(sonuc);                   
  //delay(2500);                    // 2500 ekranda yazı kalma süresi
} 
} 
}
delay(500);    // 5 sn sistem kapalı kalacak sonra devam edecek


digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
 
safetyDistance = distance;
if (distance <=3)
{
  digitalWrite(level5, HIGH);  
}

else 
{
  digitalWrite(level5, LOW);
}

if (distance <=3)
{
  digitalWrite(level4, HIGH);
  delay(5000);
  digitalWrite(level4, LOW);
  delay(5000); 
}

else 
{
  digitalWrite(level4, LOW); 
}

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

if (distance <=3)
{
  digitalWrite(level2, LOW);
  digitalWrite(level3, LOW);
  digitalWrite(level1, LOW);
  delay(10000);
}

Serial.print("Distance: ");
Serial.println(distance);

 lcd.setCursor(0, 0);
lcd.println(distance);
delay(100);
lcd.setCursor(0, 0);
lcd.clear();
} 
