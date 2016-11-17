/**
 * Inspired from Arduino ShiftOut tutorial.
 * Counts up to 255 with 8 LEDs and down from 255 with another 8 LEDs.
 */


//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

int arrFirstNumbersToDisplay[] = { 2, 1, 4, 8, 16, 32, 64, 128 };
int arrSecondNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrThirdNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int arrIndex = 0; arrIndex < 8; arrIndex++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, arrThirdNumbersToDisplay[arrIndex]);
    shiftOut(dataPin, clockPin, MSBFIRST, arrSecondNumbersToDisplay[arrIndex]);
    shiftOut(dataPin, clockPin, MSBFIRST, arrFirstNumbersToDisplay[arrIndex]);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(200);
  }
}


