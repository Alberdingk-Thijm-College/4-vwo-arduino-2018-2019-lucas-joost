int stoplichtnummer = 1;  //geeft aan bij welk stoplicht de roulatie is
int i = 0;                //de variabele die gebruikt wordt om te het aantal herhalingen te tellen tijdens het gebruik van de "for" functie

void setup(){
  pinMode(13,OUTPUT);     //lamp van stoplicht 1: rood 
  pinMode(12,OUTPUT);     //lamp van stoplicht 1: groen 
  pinMode(11,OUTPUT);     //lamp van stoplicht 1: rood  
  pinMode(10,OUTPUT);     //lamp van stoplicht 1: groen 
  pinMode(9,OUTPUT);      //lamp van stoplicht 1: rood 
  pinMode(8,OUTPUT);      //lamp van stoplicht 1: groen 
  pinMode(7,OUTPUT);      //lamp van stoplicht 1: rood 
  pinMode(6,OUTPUT);      //lamp van stoplicht 1: groen 
  pinMode(5,OUTPUT);      //lamp van voetgangers: groen
  pinMode(4,OUTPUT);      //deze output reset de flipflop die wordt gebruikt om te onthouden of er op de knop voor voetgangers is gedrukt
  pinMode(3,OUTPUT);      //deze output reset de flipflop die wordt gebruikt om te onthouden of er op de knop voor de buslijn is gedrukt
  pinMode(2,INPUT);       //deze input ontvangt de staat van flipflop die wordt gebruikt om te onthouden of er op de knop voor voetgangers is gedrukt
  pinMode(1,INPUT);       //deze input ontvangt de staat van flipflop die wordt gebruikt om te onthouden of er op de knop voor de buslijn is gedrukt 
  digitalWrite(13,HIGH);  //rode licht van stoplicht 1 aan zetten
  digitalWrite(11,HIGH);  //rode licht van stoplicht 2 aan zetten
  digitalWrite(9,HIGH);   //rode licht van stoplicht 3 aan zetten
  digitalWrite(7,HIGH);   //rode licht van stoplicht 4 aan zetten
}

void stopLicht(int stoplichtnummer){
    int lamp = 14 - (stoplichtnummer * 2);    //groene lamp bepalen
    int rood = lamp + 1;                      //rode lamp bepalen aan de hand van de groene lamp     
    digitalWrite(rood,LOW);                   //rode lamp uit doen
    digitalWrite(lamp,HIGH);                  //groene lamp aan doen
    delay(5000);                              //5 seconden aan houden
      for (i = 0;i < 4; i++){                 //5 keer laten knipperen
        digitalWrite(lamp,LOW);                   
        delay(75);
        digitalWrite(lamp,HIGH);
        delay(75);
      }
    digitalWrite(lamp,LOW);                   //groene lamp uit doen
    digitalWrite(rood,HIGH);                  //rode lamp aan doen
    next();
}

void voetganger(){
    digitalWrite(5, HIGH);    //10 seconden groen laten branden
    delay(10000);
    for (i = 0;i < 4; i++){   //5 keer laten knipperen
      digitalWrite(5,LOW);
      delay(75);
      digitalWrite(5,HIGH);
      delay(75);
    }
    digitalWrite(5,LOW);      //groene licht uit zetten
    digitalWrite(4, HIGH);    //voert stroom naar de flipflop om deze te resetten, hierdoor kan er weer opnieuw op de knop gedrukt worden
    delay(1);                 //zorgt voor vertraging tussen het aan en uit zetten van de reset van de flipflop
    digitalWrite(4, LOW);     //stopt de stroom naar de reset van de flipflop
    delay(999)                //zorgt voor extra vertraging tussen de laatste lopende voetgangers en het volgende licht wat groen wordt
}
    

void buslijn() {
    if (digitalRead(1)==HIGH) {     //leest de output van de flipflop voor de buslijn
      stopLicht(1);                 //zet stoplicht 1 (kant van buslijn) op groen
      if (stoplichtnummer == 1) {   //checkt of stoplicht 1 hierna weer aan de beurt is
        int stoplichtnummer = 2;    //voorkomt dat stoplicht 1 nog een keer aan gaat en slaat deze over
      }
    }
}

void next() {                                    //deze functie zet de roulatie voort door de variabele "stoplichtnummer" te veranderen
    if (stoplichtnummer==4){                     //checkt of de roulatie af gerond is
      int stoplichtnummer = 1;                   //zet de roulatie weer op 1
    }
    else{
      int stoplichtnummer = stoplichtnummer + 1; //verzet de roulatie naar het volgende stoplicht (1 naar 2, 2 naar 3, 3 naar 4)
    }
}


void loop() {
  buslijn();                                            //via commando bus checken en deze met stoplicht 1 laten rijden
  if (stoplichtnummer == 1 and digitalRead(2) ==HIGH){  //checkt en laat door als stoplicht 1 aan de beurt is en er voetgangers zijn
    voetganger();                                       //zet de stoplichten voor de voetgangers aan
  } 
  else {
    stopLicht(stoplichtnummer);                         //zet het stoplicht wat aan de beurt is in de roulatie aan   
  }
  delay(1000);
}
