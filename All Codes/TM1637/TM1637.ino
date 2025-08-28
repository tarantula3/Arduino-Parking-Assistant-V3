#include <TM1637Display.h>

// Define the pins connected to the TM1637
#define CLK 8
#define DIO 9

// Create a TM1637 display object
TM1637Display display(CLK, DIO);

void setup() {
  // Set the display brightness (0-7, 7 is brightest)
  display.setBrightness(7);
}

void loop() {
  // Example: Displaying a number
  int number = 1234;
  display.showNumberDec(number);
  delay(1000);

  // Example: Clearing the display
  display.clear();
  delay(500);

  // Example: Displaying custom characters (e.g., colon)
  uint8_t colon[4] = {
    display.encodeDigit(0) | 0b10000000, // Digit 0 with colon
    display.encodeDigit(0),             // Digit 0 without colon
    display.encodeDigit(0) | 0b10000000, // Digit 0 with colon
    display.encodeDigit(0)              // Digit 0 without colon
  };
  display.setSegments(colon);
  delay(1000);
}