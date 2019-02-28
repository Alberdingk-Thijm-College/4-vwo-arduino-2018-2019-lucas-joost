/*Stoplichten Opdracht Aruino - Informatica - 2018/2019 - Door Joost Noort en Lucas Schut (Docent: Wim van der Weiden)
Met onze lessen voor informatica hebben wij de opdracht gekregen om m.b.v. arduino een stoplicht te programmeren en ontwerpen.
We hebben de opdracht al een tijdje geleden op gekregen en hebben een paar dagen na de tweedeles een andere manier van aanpak gekozen.
Hier is wat uitleg over onze aanpak:
We hebben een kruispunt waar we stoplichten op willen zetten: vier "units", voor elke autobaan 1. 
Dit houdt in dat we één rood en één groen licht hebben voor de vier autobanen van het kruispunt.
Deze units worden allemaal bestuurd met dezelfde functie: "stoplicht(roulatiepunt)" die aan de hand van de input weet welke unit deze aan moet sturen.
BEL:Omdat we geen oranje led lamp hebben laten we de groene lamp eerst even knipperen voordat deze weer uit gaat.
De input van de stoplichtfunctie hangt af van de "roulatie". De roulatie is niets meer dan een woord voor de rondes die het stoplicht maakt of de volgorde 
waarin de verschillende units achter elkaar aan en uit gaan. Zo gaat eerst unit 1, dan unit 2, t/m 4 en dan begint de roulatie weer opnieuw.
Het herhalen van het stoplichtcommando binnen de roulatie en het herhalen van de roulatie zelf gebeurt met behulp van de "void loop" en de "next()" functie die we hebben gemaakt.
De next() functie verzet het "roulatiepunt", de variabele die bij houdt bij welk stoplicht de roulatie zijn, naar de volgende unit of verzet deze weer naar 1 wanneer het roulatiepunt op 4 staat.
Daarna wordt alles binnen de loop herhaald waardoor de goede unit weer wordt gekozen en de goede lampen weer op groen springen.

Voetgangers,
Voetgangers moeten
*/

int roulatiepunt = 1;  //geeft aan bij welk stoplicht de roulatie is
int i = 0;                //de variabele die gebruikt wordt om te het aantal herhalingen te tellen tijdens het gebruik van de "for" functie
int ir = 0;               //wordt gebruikt om het aantal herhalingen te tellen bij de "vertraag" functie inplaats van i
int voetganger_knop = 0;        //onthoudt of de knop voor voetgangers in gedrukt is geweest
int bus_knop = 0;         //onthoudt of de knop voor de buslijn in gedrukt is geweest

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
  pinMode(4,INPUT);       //knop van voetgangers
  pinMode(3,INPUT);       //knop van busschauffeur  
  digitalWrite(13,HIGH);  //rode licht van stoplicht 1 aan zetten
  digitalWrite(11,HIGH);  //rode licht van stoplicht 2 aan zetten
  digitalWrite(9,HIGH);   //rode licht van stoplicht 3 aan zetten
  digitalWrite(7,HIGH);   //rode licht van stoplicht 4 aan zetten
}

void stopLicht(int roulatie){
    int lamp = 14;
    lamp = lamp - (roulatie * 2);    //bepaalt, aan de hand van het "roulatiepunt" / de roulatie, wat de groene lamp van de unit is
    int rood = lamp + 1;                      //bepaalt, aan de hand van de poort van de groene lamp, wat de rode lamp van de unit is     
    digitalWrite(rood,LOW);                   //rode lamp uit doen
    digitalWrite(lamp,HIGH);                  //groene lamp aan doen
    vertraag(5000);                              //5 seconden aan houden
      for (i = 0;i < 4; i++){                 //5 keer laten knipperen
        digitalWrite(lamp,LOW);                   
        vertraag(75);
        digitalWrite(lamp,HIGH);
        vertraag(75);
      }
    digitalWrite(lamp,LOW);                   //groene lamp uit doen
    digitalWrite(rood,HIGH);                  //rode lamp aan doen
}

void voetganger(){
    if (roulatiepunt == 1 and voetganger_knop == 1){    //checkt en laat door wanneer de roulatie op 1 is en er een voetganger op de voetgangersknop heeft gedrukt bij 1 van de stoplichten
    digitalWrite(5, HIGH);    //10 seconden groen laten branden
    vertraag(10000);
    for (i = 0;i < 4; i++){   //5 keer laten knipperen
      digitalWrite(5,LOW);
      vertraag(75);
      digitalWrite(5,HIGH);
      vertraag(75);
    }
    digitalWrite(5,LOW);      //groene licht uit zetten
    digitalWrite(4, HIGH);    //voert stroom naar de flipflop om deze te resetten, hierdoor kan er weer opnieuw op de knop gedrukt worden
    vertraag(1);                 //zorgt voor vertraging tussen het aan en uit zetten van de reset van de flipflop
    digitalWrite(4, LOW);     //stopt de stroom naar de reset van de flipflop
    vertraag(999);                //zorgt voor extra vertraging tussen de laatste lopende voetgangers en het volgende licht wat groen wordt
    voetganger_knop = 0;
    buslijn();
    }
}
    

void buslijn() {
    if (bus_knop==HIGH) {           //kijkt of de knop voor de buslijn in gedrukt is geweest
      stopLicht(1);}                //zet stoplicht 1 (kant van buslijn) op groen
      bus_knop = 0;                 //zet de variabele die onthoudt of er een bus is weer op 0 zodat het systeem weet dat de bus die er net was nu weg is
    if (roulatiepunt == 1 and bus_knop==HIGH){   //checkt of stoplicht 1 hierna weer aan de beurt is
      int roulatiepunt = 2;    //voorkomt dat stoplicht 1 nog een keer aan gaat en slaat deze over
    }
}

void next() {                                    //deze functie zet de roulatie voort door de variabele "roulatiepunt" te veranderen
    if (roulatiepunt==4){                        //checkt of de roulatie af gerond is
      int roulatiepunt = 0;                      //zet de roulatie weer op 1
    }
    ++roulatiepunt; //verzet de roulatie naar het volgende stoplicht (1 naar 2, 2 naar 3, 3 naar 4)
}

void vertraag(int tijd){
  for (ir = 0;ir < tijd; ir++){
    if (digitalRead(4) == HIGH){
      voetganger_knop=1;
    }
    if (digitalRead(3) == HIGH){
      bus_knop = 1;
    }
    delay(1);
  }
}

void loop() {
  buslijn();                                            //checkt of er een busschauffeur op de knop voor bussen heeft gedrukt (zie opdracht) en laat deze, in dat geval, rijden door baan 1 op groen te zetten
  voetganger();                                         //zet de stoplichten voor de voetgangers van alle kanten indien dezen aanwezig zijn en checkt daarna weer voor bussen BEL:(met 1 led die voor allen geldt omdat we er niet genoeg hadden) 
  stopLicht(roulatiepunt);                              //zet het stoplicht wat aan de beurt is in de roulatie aan   
  next();
  vertraag(1000);
}
