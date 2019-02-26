int roulatiepunt = 1;           //geeft aan bij welk stoplicht de roulatie is
int i = 0;                      //de variabele die gebruikt wordt om te het aantal herhalingen te tellen tijdens het gebruik van de "for" functie
int ir = 0;                     //wordt gebruikt om het aantal herhalingen te tellen bij de "vertraag" functie inplaats van i
int voetganger_knop = 0;        //onthoudt of de knop voor voetgangers in gedrukt is geweest
int bus_knop = 0;               //onthoudt of de knop voor de buslijn in gedrukt is geweest
int voetgangerslicht_bezig = 0;
int voetgangerslicht_bezig_teller = 0;

void setup(){             //dit wordt gebruikt om de arduino te laten weten of er stroom van verschillende kabels ontvangen of verstuurd moet worden en zet de rode lichten aan.
  pinMode(13,OUTPUT);     //lamp van stoplicht 1: rood 
  pinMode(12,OUTPUT);     //lamp van stoplicht 1: groen 
  pinMode(11,OUTPUT);     //lamp van stoplicht 1: rood  
  pinMode(10,OUTPUT);     //lamp van stoplicht 1: groen 
  pinMode(9,OUTPUT);      //lamp van stoplicht 1: rood 
  pinMode(8,OUTPUT);      //lamp van stoplicht 1: groen 
  pinMode(7,OUTPUT);      //lamp van stoplicht 1: rood 
  pinMode(6,OUTPUT);      //lamp van stoplicht 1: groen 
  pinMode(5,OUTPUT);      //lamp van voetgangers: groen
  pinMode(4,INPUT);       //knop van voetgangers
  pinMode(3,INPUT);       //knop van busschauffeur  
  pinMode(2,OUTPUT);
  digitalWrite(13,HIGH);  //rode licht van stoplicht 1 aan zetten
  digitalWrite(11,HIGH);  //rode licht van stoplicht 2 aan zetten
  digitalWrite(9,HIGH);   //rode licht van stoplicht 3 aan zetten
  digitalWrite(7,HIGH);   //rode licht van stoplicht 4 aan zetten
}
void vertraag(int tijd){
  for (ir = 0;ir < tijd; ir++){
    if (digitalRead(4) == HIGH){
      voetganger_knop=1;
    }
    if (digitalRead(3) == HIGH){
      bus_knop = 1;
    }
    if (voetgangerslicht_bezig == 1){
      if (voetgangerslicht_bezig_teller<300 or (800< voetgangerslicht_bezig_teller < 1100) or (1600<voetgangerslicht_bezig_teller<1900) or (2400<voetgangerslicht_bezig_teller<2700) or (3200<voetgangerslicht_bezig_teller<3500)){
        tone(2,300);
      }else{
        noTone(2); 
      }
      ++voetgangerslicht_bezig_teller;
      if (voetgangerslicht_bezig_teller>=4000){
        voetgangerslicht_bezig_teller = 0;
      }
    }
    delay(1);
  }
}
void stopLicht(int roulatie){        //zet t stoplicht van de unit die nu aan de buurt is aan
    int lamp = 14 - (roulatie * 2);  //bepaalt, aan de hand van het "roulatiepunt" / de roulatie, wat de groene lamp van de unit is
    int rood = lamp + 1;             //bepaalt, aan de hand van de poort van de groene lamp, wat de rode lamp van de unit is     
    digitalWrite(rood,LOW);          //zet de rode lamp uit
    digitalWrite(lamp,HIGH);         //zet de groene lamp aan
    vertraag(2000);                  //houdt deze 5 seconden aan
    if (roulatiepunt == 1){
      bus_knop = 0;
    }
      for (i = 0;i < 4; i++){        //laat de groene lamp 5 keer knipperen
        digitalWrite(lamp,LOW);                   
        vertraag(75);
        digitalWrite(lamp,HIGH);
        vertraag(75);
      }
    digitalWrite(lamp,LOW);          //zet de groene lamp uit
    digitalWrite(rood,HIGH);         //zet de rode lamp uit
}

void voetgangerslicht(){
    if (roulatiepunt == 1 and voetganger_knop == 1){    //checkt en laat door wanneer de roulatie op 1 is en er een voetganger op de voetgangersknop heeft gedrukt bij 1 van de stoplichten
      if (bus_knop==1){
        stopLicht(1);
        bus_knop=0;
      }
      voetgangerslicht_bezig = 1;
      digitalWrite(5, HIGH);                            //laat het voetgangerslicht 10 seconden branden
      vertraag(5000);
    for (i = 0;i < 4; i++){                             //laat het licht 5 keer knipperen
      digitalWrite(5,LOW);
      vertraag(75);
      digitalWrite(5,HIGH);
      vertraag(75);
    }
    digitalWrite(5,LOW);                                //zet groene licht uit
    voetganger_knop = 0;                                //geeft weer aan dat er geen voetgangers meer staan bij de stoplichten
    vertraag(1000);                                     //zorgt voor extra vertraging tussen de laatste lopende voetgangers en het volgende licht wat groen wordt
    voetgangerslicht_bezig = 0;
    voetgangerslicht_bezig_teller = 0;
    }
}
    

void buslijn(){
    if (bus_knop==1 and roulatiepunt!= 1) {           //kijkt of de knop voor de buslijn in gedrukt is geweest en 
      stopLicht(1);}                                         //zet stoplicht 1 (kant van buslijn) op groen
      bus_knop = 0;                                          //zet de variabele die onthoudt of er een bus is weer op 0 zodat het systeem weet dat de bus die er net was nu weg is
    }

void next() {                                    //deze functie zet de roulatie voort door de variabele "roulatiepunt" te veranderen
    if (roulatiepunt==4){                        //checkt of de roulatie af gerond is
      roulatiepunt = 0;                      //zet de roulatie weer op 1
    }
    ++roulatiepunt; //verzet de roulatie naar het volgende stoplicht (1 naar 2, 2 naar 3, 3 naar 4)
}

void loop() {
  buslijn();                                            //checkt of er een busschauffeur op de knop voor bussen heeft gedrukt (zie opdracht) en laat deze, in dat geval, rijden door baan 1 op groen te zetten
  voetgangerslicht();                                         //zet de stoplichten voor de voetgangers van alle kanten indien dezen aanwezig zijn en checkt daarna weer voor bussen BEL:(met 1 led die voor allen geldt omdat we er niet genoeg hadden)   
  stopLicht(roulatiepunt);                              //zet het stoplicht wat aan de beurt is in de roulatie aan   
  next();                                               //zorgt ervoor dat de roulatie weer verder gaat
  vertraag(1000);                                       //zorgt voor vertraging
}
