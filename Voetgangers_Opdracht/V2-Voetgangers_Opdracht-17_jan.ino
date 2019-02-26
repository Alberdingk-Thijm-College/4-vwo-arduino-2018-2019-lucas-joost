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
Voetgangers moeten op een knop drukken om aan het stoplicht te laten weten dat ze aanwezig zijn, hiermee wordt voetganger_knop op 1 gezet. Als voetganger_knop op 0 staat worden de voetgangers in de roulatie over geslagen. 
In de roulatie zijn ze een soort nummer 0: voordat de auto-stoplichten op groen worden gezet wordt er gekeken of de roulatie net opnieuw begint en of er voetgangers aanwezig zijn/op de knop hebben gedrukt.
Wanneer dit zo is, gaan de stoplichten voor de voetgangers van alle kanten op groen. Deze blijven langer groen dan de lichten voor de auto's.
Hierna wordt voetganger_knop weer op 0 gezet.

Bussen,
De buslijn gaat alleen over baan 1. Aan het begin van elke herhaling, voor de voetgangers en de rest van de auto's, wordt gecheckt op bussen en, wanneer aanwezig, gaat baan 1 op groen.
De busshauffeurs drukken in de bus op een knop als ze het stoplicht naderen, hierbij wordt bus_knop op 1 gezet. 
Na het uit voeren wordt bus_knop op weer op 0 gezet
Als baan 1 al aan de beurt was in de roulatie wordt dit gelijk door gezet naar 2 maar wordt er eerst gecheckt op voetgangers om te voorkomen dat die weer een ronde moeten wachten.

Vertraag(),
Dit programma maakt gebruik van een functie die we vertraag() genoemd hebben. De vertraag() functie is verantwoordelijk voor het waar nemen van de staten van
*/

int roulatiepunt = 1;           //geeft aan bij welk stoplicht de roulatie is
int i = 0;                      //de variabele die gebruikt wordt om te het aantal herhalingen te tellen tijdens het gebruik van de "for" functie
int ir = 0;                     //wordt gebruikt om het aantal herhalingen te tellen bij de "vertraag" functie inplaats van i
int voetganger_knop = 0;        //onthoudt of de knop voor voetgangers in gedrukt is geweest
int bus_knop = 0;               //onthoudt of de knop voor de buslijn in gedrukt is geweest

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
    delay(1);
  }
}
void stopLicht(int roulatie){        //zet t stoplicht van de unit die nu aan de buurt is aan
    int lamp = 14 - (roulatie * 2);  //bepaalt, aan de hand van het "roulatiepunt" / de roulatie, wat de groene lamp van de unit is
    int rood = lamp + 1;             //bepaalt, aan de hand van de poort van de groene lamp, wat de rode lamp van de unit is     
    digitalWrite(rood,LOW);          //zet de rode lamp uit
    digitalWrite(lamp,HIGH);         //zet de groene lamp aan
    vertraag(2000);                  //houdt deze 5 seconden aan
      for (i = 0;i < 4; i++){        //laat de groene lamp 5 keer knipperen
        digitalWrite(lamp,LOW);                   
        vertraag(75);
        digitalWrite(lamp,HIGH);
        vertraag(75);
      }
    digitalWrite(lamp,LOW);          //zet de groene lamp uit
    digitalWrite(rood,HIGH);         //zet de rode lamp uit
    if (roulatiepunt == 1){
      bus_knop = 0;
    }
}

void voetgangerslicht(){
    if (roulatiepunt == 1 and voetganger_knop == 1){    //checkt en laat door wanneer de roulatie op 1 is en er een voetganger op de voetgangersknop heeft gedrukt bij 1 van de stoplichten
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
    }
}
    

void buslijn(){
    if (bus_knop==HIGH and roulatiepunt!= 1) {           //kijkt of de knop voor de buslijn in gedrukt is geweest en 
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
