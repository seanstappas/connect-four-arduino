/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int btnPin0 = 9;
const int btnPin1 = 2;
const int btnPin2 = 3;
const int btnPin3 = 4;
const int btnPin4 = 5;
const int btnPin5 = 6;
const int btnPin6 = 7;
const int btnPin7 = 8;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

int arrFirstNumbersToDisplay[] = { 2, 1, 4, 8, 16, 32, 64, 128 };
int arrSecondNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrThirdNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrFourthNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrFifthNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrSixthNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrSeventhNumbersToDisplay[] = { 128, 64, 16, 8, 2, 4, 1, 32 };
int arrEighthNumbersToDisplay[] = { 128, 64, 16, 4, 2, 8, 32, 1 };
int arrNinthNumbersToDisplay[] = { 2, 32, 16, 0, 0, 4, 8, 1 };

int arrShiftIndexToNumbers[][8] = {
  { 2, 1, 4, 8, 16, 32, 64, 128 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 128, 64, 16, 8, 2, 4, 1, 32 },
  { 2, 32, 16, 0, 0, 4, 8, 1 }
};

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(btnPin0, INPUT);
  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  pinMode(btnPin3, INPUT);
  pinMode(btnPin4, INPUT);
  pinMode(btnPin5, INPUT);
  pinMode(btnPin6, INPUT);
  pinMode(btnPin7, INPUT);
}

int clickedIndex = 0;

int clicked = LOW;

void loop() {
  //  for (int btnIndex = 0; btnIndex < 8; btnIndex++) {
  //    buttonState = digitalRead(btnIndex);
  //    if (buttonState == HIGH) {
  //      break;
  //      clickedIndex = btnIndex;
  //    }
  //    else {
  //      clickedIndex = -1;
  //    }
  //  }

  // count from 0 to 255 and display the number
  // on the LEDs
  for (int arrIndex = 0; arrIndex < 8; arrIndex++) {
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    //
    //    for (int shiftRegIndex = 8; shiftRegIndex > -1; shiftRegIndex--) {
    //      if (shiftRegIndex == clickedIndex){
    //        shiftOut(dataPin, clockPin, MSBFIRST, arrShiftIndexToNumbers[clickedIndex][arrIndex]);
    //      }
    //      else{
    //        shiftOut(dataPin, clockPin, MSBFIRST, 0);
    //      }
    //    }

    for(int i=2; i<10; i++){
      if(digitalRead(i) == HIGH){
        clicked = HIGH;
        break;
      }
      clicked = LOW;
    }


    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (clicked == HIGH) {
      shiftOut(dataPin, clockPin, MSBFIRST, arrNinthNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrEighthNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrSeventhNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrSixthNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrFifthNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrFourthNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrThirdNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrSecondNumbersToDisplay[arrIndex]);
      shiftOut(dataPin, clockPin, MSBFIRST, arrFirstNumbersToDisplay[arrIndex]);
    } else {
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
      shiftOut(dataPin, clockPin, MSBFIRST, 0);
    }
//    if (clickedIndex != -1) {
//      shiftOut(dataPin, clockPin, MSBFIRST, arrNinthNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrEighthNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrSeventhNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrSixthNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrFifthNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrFourthNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrThirdNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrSecondNumbersToDisplay[arrIndex]);
//      shiftOut(dataPin, clockPin, MSBFIRST, arrFirstNumbersToDisplay[arrIndex]);
//    }

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(200);
  }
}

