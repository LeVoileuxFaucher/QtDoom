#include <main.h>

uint8_t hp = 20;
uint8_t munition = 10;
uint16_t LedState = 0b0011111111111;
float x, y, z;
uint8_t compteurBouton1 = 0;
uint8_t compteurBouton2 = 0;

bool rechargementActif = false;

unsigned long lastReloadStep = 0;
uint8_t reloadStep = 0;
unsigned long reloadInterval = 0;

int cursorX;
int cursorY;

bool bouton1 = 0;  
bool bouton2 = 0;

void setup() {
  bitSet(LedState, 11);
  Serial.begin(9600);
  SetupLed();
  joystick_setup();
  bouton_update();
  setup_encoder(2, 3);
  SetupAccelerometre();
  SetupLCD();
  CalibrerAccelerometre(100);
}

void loop() {
  
  if (bouton1_vient_detre_appuye())
{
    bouton1 = 1;
    compteurBouton1++;
}
else
{
    bouton1 = 0;
}

if (bouton2_vient_detre_appuye())
{
    bouton2 = 1;
    compteurBouton2++;
}
else
{
    bouton2 = 0;
}
  getCursorPosition(cursorX, cursorY, 128, 64);
    
  if (bouton1)
  {
    if (munition > 0)
    {
      munition--;
      LedState = ShiftRight(LedState);
      lcd.setCursor(0, 0);
      lcd.print("Munition: ");
      lcd.print(munition);
      lcd.print(" ");
      
    }
    bitSet(LedState, 11); //led rouge
    
  }
  else
  {
    bitClear(LedState, 11); //led rouge
  }
  if ((munition < 10) && bouton2 && !rechargementActif)
{
    rechargementActif = true;

    reloadStep = munition;

    reloadInterval = 3500 / 10 - munition;
    lastReloadStep = millis();
    CalibrerAccelerometre(100);
}

  UpdateReloadAnimation();
  WriteTrame();
  //ReadTrame();
  bouton_update();
  UpdateLed(LedState); 
}

void WriteTrame() {

    static unsigned long previousMillis = 0;
    const unsigned long interval = 12;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {

        previousMillis = currentMillis;

        uint8_t boutons = 0;

        
        if (compteurBouton1 > 0)
        {
            boutons |= (1 << 0);
            compteurBouton1--;
        }
        else if (compteurBouton2 > 0)
        {
            boutons |= (1 << 1);
            compteurBouton2--;
        }

        Serial.write('$');
        Serial.write(munition);
        Serial.write(getJoystickMappedX());
        Serial.write(getJoystickMappedY());
        Serial.write(boutons);
        Serial.write(int8_t(read_encoder()));
        Serial.write(uint8_t(cursorX));
        Serial.write(uint8_t(cursorY));
        Serial.write('#');
    }
}

void ReadTrame() {
  if (Serial.available() > 0) {
    char startChar = Serial.read();
    if (startChar == '$') {
      String data = Serial.readStringUntil('#');
      hp = data.toInt(); // Exemple de conversion en entier 
    }
  }
}


void UpdateReloadAnimation()
{
    if (!rechargementActif) return;

    unsigned long currentMillis = millis();

    if (currentMillis - lastReloadStep >= reloadInterval)
    {
        lastReloadStep = currentMillis;

        if (reloadStep < 10)
        {
            reloadStep++;
            munition = reloadStep;

            LedState = (LedState & 0b110000000000) | ((1 << reloadStep) - 1);

            lcd.setCursor(0,0);
            lcd.print("Munition: ");
            lcd.print(munition);
            lcd.print(" ");
        }
        else
        {
            rechargementActif = false;
        }
    }
}