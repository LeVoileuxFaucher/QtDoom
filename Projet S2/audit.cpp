#include <main.h>

uint16_t LedState = 0b00111111111;
int lastValue = 0;
float x, y, z;
int ancienToursEncodeur = 0;

void setup()
{
  bitSet(LedState, 10);
  Serial.begin(9600);
  SetupLed();
  joystick_setup();
  bouton_update();
  setup_encoder(2, 3);
  SetupAccelerometre();
  SetupLCD();
  CalibrerAccelerometre(100);
}

void loop()
{
  int ToursEncodeur = getEncoderdiff();

  lireAxes(x, y, z);
  uint16_t pot = analogRead(A5);

  LedState = CalculeBargraph(pot);

  if (ancienToursEncodeur != ToursEncodeur)
  {
    ancienToursEncodeur = ToursEncodeur;
    lcd.clear();
  }
  switch (ToursEncodeur)
  {
  case 0:
    AfficheMouvAcc(detecterMouvement(x, y, z));
    AfficheRotationAcc(x, y, z);
    if (!bouton1_est_appuye()||!bouton2_est_appuye())
    {
      CalibrerAccelerometre(100);
    }
    break;

  case 1:
    AfficheEncodeur(read_encoder());
    AffichePot(pot);
    break;

  case 2:
    AfficheJoystick(readJoystick_x(), readJoystick_y());
    break;

  case 3:
    AfficheBouton(bouton1_est_appuye(), bouton2_est_appuye());
    break;

  case 4:

    break;

  default:
    LedState = 0b111111111111; 
    AfficheMessage("Erreur");
    break;
  }

  if (ToursEncodeur == 4)
  {
    UpdateLed(LedState);
  }
  else
  {
    UpdateLed(1);
  }

  bouton_update();
}