#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//constants for LEDs
int greenLED = 12;
int redLED = 13;

//set our code
const char* ourCode = "1234";
int currentPosition = 0;

const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[rows] = {9, 8, 7, 6}; 
byte colPins[cols] = {5, 4, 3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  //lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  
  displayCodeEntryScreen();
  
  //setup and turn off both LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  
  
}

void loop()
{
  int l;
  
  char key = keypad.getKey();
  
  if (int(key) != 0) {
    lcd.setCursor(6,1);
    lcd.print("    ");
    lcd.setCursor(6,1);
    
    for (l=0; l<=currentPosition; ++l)
    {
      lcd.print("*");
    }
    
    if (key == ourCode[currentPosition])
      {
        ++currentPosition;
        if (currentPosition == 4)
        {
          unlockDoor();
          currentPosition = 0;
        }
      } else {
        invalidCode();
        currentPosition = 0;
      }
    
    
  }
}

void invalidCode()
{
  
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("NESPRAVNE");
  lcd.setCursor(0,1);
  lcd.print("HESLO");

  
  delay(5000);
  
  displayCodeEntryScreen();
}

void unlockDoor()
{
    digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("POBOCKA");
  lcd.setCursor(0,1);
  lcd.print("ODKODOVANA");
  
  //add any code to unlock the door here
  delay(10000);
  digitalWrite(greenLED, LOW);
  displayCodeEntryScreen();
}

void displayCodeEntryScreen()
{
  digitalWrite(redLED, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print("ZAKODOVANE");
  lcd.setCursor(0,1);
  lcd.print("HESLO:");
}

void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print("                    ");
}
