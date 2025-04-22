// PROJECT  :RPN Calculator
// PURPOSE  :
// COURSE   :ISC3U-E
// AUTHOR   :N.ANDREW
// DATE     :2025 04 04
// MCU      :328P (Standalone)
// STATUS   :Working
// REFERENCE:https://docs.arduino.cc/language-reference/en/functions/advanced-io/shiftOut/

#include "Stack.h"
#include <LiquidCrystal.h>

// LCD pin config
const int RS = 9, EN = 8, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

Stack stack;

String input = ""; // buffer for building numbers

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);     // 16x2 LCD
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("RPN Calculator");  // Initial message
  while (!Serial);
}

char getKey() {
  uint16_t value = 0;

  // Wait for a non-zero read (only once)
  while ((value = analogRead(A5)) == 0);

  delay(100);
  value = analogRead(A5); // Read again after small delay

  if (value == 0) {
    return '\0';  // No good key pressed
  }

  uint16_t thresholds[] = { 55, 58, 62, 66, 75, 81, 88, 97, 116, 132, 152, 179, 255, 341, 512, 1024 };
  char keys[] = { '+', '=', '.', '0', '-', '3', '2', '1', '*', '6', '5', '4', '/', '9', '8', '7' };
  uint8_t index = 0;
  
  while (value > thresholds[index]) {
    index++;
    if (index >= 16) return '\0';  // Safety: invalid
  }
  
  return keys[index];
}

void loop() {
  char key = getKey();
if (key == '\0') {
return;  // No key pressed, skip rest of loop
}
  Serial.print("Key Pressed: ");
  Serial.println(key);

  if (key == '=') {
    if (input.length() > 0) {
      float num = input.toFloat(); // convert input to float
      stack.push(num);

      lcd.clear();
      lcd.setCursor(0, 1); // Only display number on 2nd row
      lcd.print(num, 4);

      Serial.print("Pushed: ");
      Serial.println(num, 4);
      input = ""; // clear buffer
    }
  } else if (isdigit(key) || key == '.') {
    input += key;
    Serial.print("Input buffer: ");
    Serial.println(input);
  } else {
    if (!stack.isEmpty()) {
      float b = stack.pop();
      float a = stack.pop();
      float result = 0;

      switch (key) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
          if (b != 0) {
            result = a / b;
          } else {
            Serial.println("Error: divide by zero");
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Err: /0");
            delay(1000);
            lcd.clear();
            return;
          }
          break;
        default:
          Serial.println("Unhandled operator");
          return;
      }

  stack.push(result);

    lcd.clear();
      if (result < 10){
        lcd.setCursor(5, 1);
      }
        else if (result >= 10 && result < 1000){
        lcd.setCursor(4, 1);
      }
        else if (result >= 1000 && result < 100000){
        lcd.setCursor(3, 1);
      }
        else if (result >= 100000 && result < 10000000){
        lcd.setCursor(2, 1);
      }
        else if (result >= 10000000 && result < 1000000000){
        lcd.setCursor(1, 1);
      }
      else{
        lcd.setCursor(0,1);
      }

lcd.print(result, 4);  // Always 4 decimal places
      Serial.print("Result pushed: ");
      Serial.println(result, 4);
    }
  }
}
