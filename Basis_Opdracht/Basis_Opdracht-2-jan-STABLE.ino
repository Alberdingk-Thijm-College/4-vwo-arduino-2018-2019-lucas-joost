int routaltie;
int roulatie = 1;
void setup() {
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

void loop() {
  //bus();
  //voetganger();
  stopLicht(roulatie);
  delay(1000);
  ++roulatie;
  if (roulatie > 4){
    roulatie = 1;
  }
}
