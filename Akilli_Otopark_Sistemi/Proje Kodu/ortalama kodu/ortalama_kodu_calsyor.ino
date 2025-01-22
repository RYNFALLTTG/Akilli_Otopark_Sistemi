


int sonuc;
int button=2;
float sum=0;
bool durum=true;
int i=0;
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop() {
 Serial.print("deger :");
 Serial.println(analogRead(A1));
 if(digitalRead(2)==1){
   durum=false;
   Serial.println("basildi");
 }
 if(durum==false){
   
  sum = (sum +(analogRead(A1)));
 
 if(i==10){
  sonuc=sum/10;
 Serial.print("ort_sonucu :");
 Serial.println(sonuc);
 sum=0;
 i=-1;
 durum=true;
 }
  
i=i+1;
 }
delay(1000);
}


 