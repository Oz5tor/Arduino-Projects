#include <FlexiTimer2.h>
#include <TrueRandom.h> // libary from https://code.google.com/p/tinkerit/wiki/TrueRandom

// Author: Tor Soya
// Started: 25/02/2015
// 
// Project mind rember training with score
//   each round the 5 lights goes on 
//   Press buttons belonging to the lights and the next cucle starts
//   after each succefull round the speed incereses.
//   user keep doing this until it faills
//   the user has 10sec to press in the right sequence of Led's, and the array + Tryk will reset and give a new Array
//   a score will be keept in EEprom for futhere feuters
//   !!Bonus!! Web page to show high score and currunt score
// ============ LED's =====================
const int Red        = 2; // Red Led
const int Yellow     = 7; // Yellow Led
const int Green      = 8; // Green Led
const int Correct    = 6; // Correct Led
// =========== Buttons ===================
const int btnRed     = 3;  // Red LED
const int btnYellow  = 5 ; // Yellow LED
const int btnGreen   = 9 ; // Green LED
int btnRedState      = 0;  // start state of btnRed
int btnYellowState   = 0;  // start state of btnYellow
int btnGreenState    = 0;  // start state of btnGreen
int btnState         = 0;
// ================================================
const int MAXcnt     = 5;   // antal gange at der skal være stabilt input fra switch
int LedTimesOn       = 5;   // number of High Times for the LEDs
int LedOnTime        = 500; // Time for how long the Led's are on
int faill            = 0;   // if wrong combination of button is pressed changing to 1
// ===============================
int whatLeds[5]; // declaration of array that the user has to rember
// ========== Counters ==============
int x = 0;
int currentScore = 0;
static int Tryk = 1; //
// ================================
boolean slut = false;

void setup() {
  Serial.begin(115200);
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Correct, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(btnRed, INPUT_PULLUP);
  pinMode(btnYellow, INPUT_PULLUP);
  pinMode(btnGreen, INPUT_PULLUP); 
  FlexiTimer2::set(10, keyRead); // 500ms period
  FlexiTimer2::start();
}

void loop() {
    int i = 0;
    x = 0;
    if (true == slut) {
      Serial.println(" Again ????");
      while (1){} ;
      }
      while (i < LedTimesOn) {
        int randPin = TrueRandom.random(1, 4);
       /*Serial.print("number to be placed in array at");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(randPin);*/
        delay(LedOnTime);
        switch (randPin) {
          case 1: // Red
            digitalWrite(Red, HIGH);
            delay(LedOnTime);
            break;
          case 2: // Yellow
            digitalWrite(Yellow, HIGH);
            delay(LedOnTime);
            break;
          case 3: // Green
            digitalWrite(Green, HIGH);
            delay(LedOnTime);
            break;
        } // end of switch
        whatLeds[i] = randPin;
        i++;
        digitalWrite(Red, LOW);
        digitalWrite(Yellow, LOW);
        digitalWrite(Green, LOW);
          delay(LedOnTime);
      }// end of while
       digitalWrite(Correct, HIGH);
       delay(1000);
       digitalWrite(Correct, LOW);
       delay(10000);
         Serial.println("Ny runde");
         Tryk = 1; // zeroing the Tryk counter   
    /* for(int x = 0; x < 5; x++){
        Serial.print("number there comes out of array at");
        Serial.print(x);
        Serial.print(": ");
        Serial.println(whatLeds[x]);
      }// end og check for loop */
       if (slut) {
          Serial.println("");
          Serial.print("Din score blev: ");
          Serial.println(currentScore);         
     }
     // Serial.println("faerdig.... igen !  ");
} // end of loop
void knapok(int knap, char * torsnavn) 
{
  if(Tryk <= 5) {
    if (whatLeds[x] == knap){ // hvis korrekt knap er trykke
    char tekst[] = "korrekt";
/*    Serial.print("antal tryk ");
    Serial.println(Tryk);
    Serial.println(tekst);*/
    LedOnTime = LedOnTime - 10;
    currentScore = currentScore+5;  
    Serial.println(currentScore);
    digitalWrite(Correct, HIGH);
    delay(3000);
    digitalWrite(Correct, LOW);
    }
    else{ // hvis forkert
      digitalWrite(A5, HIGH);
      delay(3000);
      digitalWrite(A5, LOW);
      Tryk = 5;
      Serial.println("--forkert");
     /* Serial.print("antal tryk ");
      Serial.println(Tryk);*/
      slut = true;
    }   
    Tryk++;
  }
}

// ====== Read BTNS ======
void keyRead(){
  static int cnt = 0;
  static boolean keyPres = false;
  if (!digitalRead(btnRed)){ // her er key trykket ned
    if (cnt < MAXcnt){ // her er knappen holdt nede
      cnt++; // vi er ved at tælle op
      if (cnt >= MAXcnt){
        if (!keyPres){
          knapok(1, "HLP");// kalder Knapok function
           ++x;
           if (sizeof( whatLeds)<= x) { x=0;};
          keyPres = true;
        }
      }
    }
  }else if (!digitalRead(btnYellow)){ // her er key trykket ned
    if (cnt < MAXcnt){ // her er knappen holdt nede
      cnt++; // vi er ved at tælle op
      if (cnt == MAXcnt){
        if (!keyPres){
          knapok(2, "kage");// kalder Knapok function
           ++x;
           if (sizeof( whatLeds)<= x) { x=0;};
          keyPres = true;
        }
      }
    }
  }else if (!digitalRead(btnGreen)){ // her er key trykket ned
    if (cnt < MAXcnt){ // her er knappen holdt nede
      cnt++; // vi er ved at tælle op
      if (cnt == MAXcnt){
        if (!keyPres){
          knapok(3, "Soya"); // kalder Knapok function
           ++x;
           if (sizeof( whatLeds)<= x) { x=0;};
          keyPres = true;
        }
      }
    }
  } else { 
    if (keyPres){ // her er tasen sluppet og vi har sendt en key til main og vi er ved at tælle ned
      cnt--;
      if (cnt == 0){
        keyPres = false;
      }
    } else {
      cnt = 0;
    }
  }
}


