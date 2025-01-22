#include <Servo.h>
#include <PCD8544.h>
Servo myservo; 
 PCD8544 lcd;
 int button=2;
int BUTTON=29;
float sonuc;

#define SENSOR_PIN 30
#define BUZZER_PIN 13
#define RELAY_PIN 8
#define SPRINKLER_START_DELAY 5000  //5 seconds 
#define SPRINKLER_ON_TIME 3000      //3 seconds Sprinkler on time
int pos = 0;
int i;
float deger;
float toplam=0;

int analogpin=5;
int sum=0;
int index=0;
int averead=0;
const int numreadings=9;

int timer1_counter;
int adc_val;
int int_flag;
int int_array[9];
float V;

const int trigPin = 36;
const int echoPin = 10;
const int level4 = 13;
const int level3 = 11;
const int level2 = 12;
const int level1 = 46;
const int level5 = 32;
 
// defines variables
long duration;
int distance;
int safetyDistance;

unsigned long previousTime = millis();
 
void setup() {

  int_flag=0;

Serial.begin(9600);
pinMode(analogpin,OUTPUT);
for(i=0; i<=8; i++){
  int_array[i]=0;
}

noInterrupts();           //

  TCCR1A = 0;
  TCCR1B = 0;


timer1_counter = 59286;  

  TCNT1 = timer1_counter;   
  TCCR1B |= (1 << CS12);    
  TIMSK1 |= (1 << TOIE1);   
  interrupts();             
}

ISR(TIMER1_OVF_vect)        
{
  TCNT1 = timer1_counter;   
  int_flag=1;  
  
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
   if (int_flag==1){
    adc_val=analogRead(A2);
    V=5.0*adc_val/1023.0;
    analogWrite(analogpin,adc_val/4);
    }
    sum=sum-int_array[i];
    int_array[i]=analogRead(A2); 
    sum=sum+int_array[i];
    index=index++;
    if(i==9){
      i=0;
    }
    averead=sum/numreadings;
    Serial.print("\n"); Serial.print("Average Filter Reading: "); 
Serial.println(averead);
    delay(1);
  unsigned long previousTime = millis();
  //If there is fire then the sensor value will be LOW else the value will be HIGH
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
      lcd.setCursor(0, 0);
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
if(digitalRead(29)==1){
Serial.println("amı patladı");

for(i=0;i<11;i++){
 toplam=distance;                                 // bu kısıma belki bir ölçüm kodu gerekebilir.
  toplam=toplam+deger;          // delay süresi ölçüm alma aralığı
  delay(1000);
if(i=10){
  sonuc=(toplam/10);                      // 10 ve 11 degeri istege göre değiştirilecek.
  lcd.setCursor(0, 0);
  lcd.print(sonuc);
  lcd.print("sonuc");
  Serial.println(sonuc);
  sonuc=0;
  delay(500);   
                
} 
}
   
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
  delay(100);
  lcd.setCursor(0, 0);
  lcd.clear();
  } 
 
 
