void setup() {
  int ped=0;
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT); //voetgangers
  pinMode(2,INPUT); //stoplichtknop
  pinMode(1,INPUT); //voetgangersknop

  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(7,HIGH);
  //variabelen
  int bus = 0;
  pedestrianloop();
}

void stopLicht(int hi){
  int lamp = 14 - (hi * 2);
  int rood = lamp+1;
  digitalWrite(rood,LOW);
  digitalWrite(lamp,HIGH);
  delay(5000);
  digitalWrite(lamp,LOW);
  delay(75);
  digitalWrite(lamp,HIGH);
  delay(75);
  digitalWrite(lamp,LOW);
  delay(75);
  digitalWrite(lamp,HIGH);
  delay(75);
  digitalWrite(lamp,LOW);
  delay(75);
  digitalWrite(lamp,HIGH);
  delay(75);
  digitalWrite(lamp,LOW);
  delay(75);
  digitalWrite(lamp,HIGH);
  delay(75);
  digitalWrite(lamp,LOW);
  digitalWrite(rood,HIGH);
}
void pedestrianloop(){
  if (digitalRead(1)==HIGH){
    int ped = 1;
    pedestrianloop();
  }
}
void pedestrian(){
  if (ped==1){
    digitalWrite(5, HIGH);
    delay(10000);
    digitalWrite(5,LOW);
    delay(75);
    digitalWrite(5,HIGH);
    delay(75);
    digitalWrite(5,LOW);
    delay(75);
    digitalWrite(5,HIGH);
    delay(75);
    digitalWrite(5,LOW);
    delay(75);
    digitalWrite(5,HIGH);
    delay(75);
    digitalWrite(5,LOW);
    delay(75);
    digitalWrite(5,HIGH);
    delay(75);
    digitalWrite(5,LOW);
    delay(1000);
  }
}

void loop() {
  //bus
  pedestrian();
  stopLicht(1);
  delay(1000);
  stopLicht(2);
  delay(1000);
  stopLicht(3);
  delay(1000);
  stopLicht(4);
  delay(1000);


}
