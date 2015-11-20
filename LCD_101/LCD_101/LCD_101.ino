#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  lcd.clear();
  // Print a message to the LCD.
}

void loop() {
  lcd.print("Kage");
}
