//Sortie bouton
const int btnPin_plus = A3;
const int btnPin_moins = A4;
const int bp_start = A5;
const int bp_mode = A2;

//Définition pin des led affichage
#define Led1 2
#define Led2 3
#define Led3 4
#define Led4 5
#define Led5 6
#define Led6 7
#define Led_depart 8
#define Led_mode 9

//Définition pin Buzzer
#define Buzzer 13
#define Sortie_circuit 10

//Variable distance
int pinTrig = 12;
int pinEcho = 11;
long temps;
float distance;

//Variable interne led
int Tab_Led[6] = { 0, 0, 0, 0, 0, 0 };
int i;
int Nbre, Nbre_copy, Quotient, Reste;

int Tab_led_sorti[6] = { 2, 3, 4, 5, 6, 7 };

//Variable bouton plus
int btnVal_plus = 0;
bool btnState_plus = false;
bool oldbtnState_plus = false;

//Variable bouton moins
int btnVal_moins = 0;
bool btnState_moins = false;
bool oldbtnState_moins = false;

//Variable bouton start
int btnVal_start = 0;
bool btnState_start = false;
bool oldbtnState_start = false;
int Depart;

//Variable bouton mode
int btnVal_mode = 0;
bool btnState_mode = false;
bool oldbtnState_mode = false;
int Mode;

void setup() {
  //definir les led en tant que sortie
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led5, OUTPUT);
  pinMode(Led6, OUTPUT);
  pinMode(Led_depart, OUTPUT);
  pinMode(Led_mode, OUTPUT);

  //definir le buzzer en sortie
  pinMode(Buzzer, OUTPUT);
  pinMode(Sortie_circuit, OUTPUT);

  //Bouton pin
  pinMode(btnPin_plus, INPUT_PULLUP);
  pinMode(btnPin_moins, INPUT_PULLUP);
  pinMode(bp_start, INPUT_PULLUP);
  pinMode(bp_mode, INPUT_PULLUP);

  //Variable capteur ultrason
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  digitalWrite(pinTrig, LOW);  

  //initialisation Variable
  Nbre = 0;
  Depart = 0;
  Mode = 0;



}


void loop() {

  Bouton_mode();


  if (Mode == 0) {
    //LedMode
    digitalWrite(Led_mode, LOW);
    //sécurité
    if (Nbre > 63) {
      Nbre = 63;
    }
    if (Nbre < 0) {
      Nbre = 0;
    }
    //Convertion en binaire

    Conv_Binaire();

    //allumage selon le tableau

    led_affichage();

    //Décompte du temps

    Timer_alarme();

    //Buzzer
   if (Nbre == 0 && Depart == 1) {
     Buzzer_alarme();
      Depart = 0;
    }


    //Choix du temps
    if (Depart == 0) {
      Boutonplus();

      Boutonmoins();
    }

    //Fonction depart
    Bouton_start();
  }
  else {
    digitalWrite(Led_mode, HIGH);

      for (i = 0; i < 6; i = i + 1) {
        digitalWrite(Tab_led_sorti[i], LOW);
      }

  digitalWrite(pinTrig, HIGH);        
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  temps = pulseIn(pinEcho, HIGH);    

  if (temps > 25000) {              
    
  }

  else {
    temps = temps/2;
    distance = (temps*340)/10000.0;                  
  }


  if (distance <= 45) {
    delay(distance/2);
    digitalWrite(Buzzer, HIGH);
    delay(distance/2);
  }
  else {
    delay(2000);
  }

  digitalWrite(Buzzer, LOW);

  }

}

void Boutonplus() { /* function testPushBtn */
  ////Read pushbutton
  btnVal_plus = analogRead(btnPin_plus);
  if (btnVal_plus < 200) {
    btnState_plus = true;
    if (oldbtnState_plus != btnState_plus) {
    }
  } else {
    btnState_plus = false;
    if (oldbtnState_plus != btnState_plus) {
      Nbre = Nbre + 1;
    }
  }
  oldbtnState_plus = btnState_plus;
}


void Boutonmoins() { /* function testPushBtn */
  ////Read pushbutton
  btnVal_moins = analogRead(btnPin_moins);
  if (btnVal_moins < 200) {
    btnState_moins = true;
    if (oldbtnState_moins != btnState_moins) {
    }
  } else {
    btnState_moins = false;
    if (oldbtnState_moins != btnState_moins) {
      Nbre = Nbre - 1;
    }
  }
  oldbtnState_moins = btnState_moins;
}



void Bouton_start() { /* function testPushBtn */
  ////Read pushbutton
  btnVal_start = analogRead(bp_start);
  if (btnVal_start < 200) {
    btnState_start = true;
    if (oldbtnState_start != btnState_start) {
    }
  } else {
    btnState_start = false;
    if (oldbtnState_start != btnState_start) {
      Depart = Depart + 1;
    }
  }
  oldbtnState_start = btnState_start;

  if (Depart > 1) {
    Depart = 1;
  }
}

void Bouton_mode() { /* function testPushBtn */
  ////Read pushbutton
  btnVal_mode = analogRead(bp_mode);
  if (btnVal_mode < 200) {
    btnState_mode = true;
    if (oldbtnState_mode != btnState_mode) {
    }
  } else {
    btnState_mode = false;
    if (oldbtnState_mode != btnState_mode) {
      Mode = Mode + 1;
    }
  }
  oldbtnState_mode = btnState_mode;

  if (Mode > 1) {
    Mode = 0;
  }
}


void Buzzer_alarme() {
  for (i = 0; i < 4000; i = i + 1) {
    digitalWrite(Sortie_circuit, HIGH);
    digitalWrite(Led1, LOW);
    digitalWrite(Buzzer, HIGH);
    delay(8);
    digitalWrite(Buzzer, LOW);
    delay(8);
  }
  digitalWrite(Led_depart, LOW);
  digitalWrite(Sortie_circuit, LOW);
}

void Conv_Binaire()
{

  Nbre_copy = Nbre;
  Quotient = Nbre;

  for (i = 0; i < 6; i = i + 1) {
    Reste = Nbre_copy % 2;
    Quotient = Nbre_copy / 2;
    Nbre_copy = Nbre_copy / 2;
    Tab_Led[i] = Reste;
  }

}

void led_affichage()
{
    for (i = 0; i < 6; i = i + 1) {

      if (Tab_Led[i] == 1) {
        digitalWrite(Tab_led_sorti[i], HIGH);
      } else {
       digitalWrite(Tab_led_sorti[i], LOW);
      }
    }  
}

void Timer_alarme()
{
      if (Nbre > 0 && Depart == 1) {
     digitalWrite(Led_depart, HIGH);
     i = 0;
      while (i < 60) {
       delay(995);
        i = i + 1;
      }
     Nbre = Nbre - 1;
    }
}