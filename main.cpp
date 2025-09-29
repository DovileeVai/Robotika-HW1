
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LED'ai
#define LED_PIN1 2
#define LED_PIN2 3
#define LED_PIN3 4
#define LED_PIN4 5
#define LED_PIN5 6

// Mygtukas
#define BUTTON_PIN 7

// Buzzeris
#define BUZZER_PIN 8

LiquidCrystal_I2C lcd(0x27, 16, 2); // adresas 0x27, ekrano matmenys 16x2

const int leds[5] = {LED_PIN1, LED_PIN2, LED_PIN3, LED_PIN4, LED_PIN5};

// pradzios laikas nuo "GO"
unsigned long startTime = 0;
// reakcijos laikas
unsigned long reactionTime = 0;

void setup()
{
  randomSeed(analogRead(A1)); // triuksmas is laisvo A1 pino nustatyto random seed
  							  // kad kiekviena karta butu vis kitoks
  
  for (int i = 0; i < 5; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // INPUT_PULLUP (paspaudus = LOW)
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.init();   // inicijuoja I2C LCD
  lcd.backlight(); // ijungia apsvietima
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("F1 reaction test");

  lcd.setCursor(0, 1);
  lcd.print("Press to start");
}

void loop()
{
  // Laukiamas tvarkingas paspaudimas (jei atsoko, griztam i pradzia)
  if (!waitButtonPress()) 
    return;
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lights...");
  
  // paeiliui ijungiami LED'ai, supypsi ir tikrinama, ar nebuvo ankstyvo paspaudimo
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(leds[i], HIGH);
    shortBeep();
    if (checkJumpStart(1000)) // jei buvo paspaudta
    { 
      showJumpStart();  // parodomas "jump start" pranesimas
      return;           // griztama i loop() pradzia
    }
  }
    
  // atsitiktinis laukimas (1-4 s) iki uzgestant visiems LED'ams
  unsigned long waitMs = random(1000, 4000);
  if (checkJumpStart(waitMs)) 
  { 
    showJumpStart(); 
    return; 
  }
  
  // uzgesta visos lemputes
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(leds[i], LOW);
  }
  
  // garsinis starto signalas
  longBeep();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GO! Press!");
  
  // laikas nuo "GO"
  startTime = millis();
  
  if(!waitButtonPress()) 
    return;
  
  // reakcijos laikas = dabartinis laikas - "GO" momentas
  reactionTime = millis() - startTime;
  
  // rezultatu pateikimas ekrane
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your time: ");
  lcd.setCursor(0, 1);
  lcd.print(reactionTime);
  lcd.print(" ms");
  
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Again?");
  lcd.setCursor(0, 1);
  lcd.print("Press the button.");
}

bool waitButtonPress()
{
  // laukiam pirmo paspaudimo
  while (!isPressed()) {}
  // trumpas uzlaikymas uztikrinti, kad tikrai paspausta
  delay(20);
  if (!isPressed()) // jei vel signalas = HIGH, tai atsoko 
    return false;   // ir toki paspaudima atmetam
  waitRelease();    // laukiame mygtuko atleidimo
  
  return true;
}  

bool isPressed()
{
  return digitalRead(BUTTON_PIN) == LOW;
}

void waitRelease()
{
  while (isPressed()) {}
  delay(5);
}

// tikrinama, ar nebuvo per anksti paspaustas mygtukas
bool checkJumpStart(unsigned long ms)
{
  unsigned long t0 = millis();
  while (millis() - t0 < ms)
  {
    if (isPressed())
    {
      delay(20);
      if (isPressed()) 
        return true;
    }
    delay(2);
  }
  return false;
}

void showJumpStart()
{
  // isjungia visus LED'us
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(leds[i], LOW);
  }
  tone(BUZZER_PIN, 400, 250);
  delay(280);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JUMP START!");
  lcd.setCursor(0, 1);
  lcd.print("Wait and retry.");
  
  waitRelease();
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press to start");
}

void shortBeep()
{
  tone(BUZZER_PIN, 2500, 100);
}

void longBeep()
{
  tone(BUZZER_PIN, 400, 400);
}

