/*
  Sequentially turns on every LED, from index 0 to 69.
 */

//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 70; i++) {
    int arrOnLeds[] = { i };
    resetShiftRegBinaryValues();
    setOnLEDs(arrOnLeds, 1);
    turnOnLEDs();
    delay(100);
  }
}

int mapLedIndexToShiftRegAndPin[70][2] = {
  {8, 1}, {8, 5}, {8, 4}, {7, 7}, {7, 6}, {7, 4}, {7, 2},
  {8, 0}, {8, 3}, {8, 2}, {7, 0}, {7, 5}, {7, 3}, {7, 1},

  {4, 3}, {4, 1}, {5, 3}, {5, 1}, {6, 3}, {6, 1}, {0, 1},
  {4, 4}, {4, 2}, {5, 4}, {5, 2}, {6, 4}, {6, 2}, {0, 0},

  {4, 6}, {4, 0}, {5, 6}, {5, 0}, {6, 6}, {6, 0}, {0, 2},
  {4, 7}, {4, 5}, {5, 7}, {5, 5}, {6, 7}, {6, 5}, {0, 3},

  {3, 3}, {3, 1}, {2, 3}, {2, 1}, {1, 3}, {1, 1}, {0, 4},
  {3, 4}, {3, 2}, {2, 4}, {2, 2}, {1, 4}, {1, 2}, {0, 5},

  {3, 6}, {3, 0}, {2, 6}, {2, 0}, {1, 6}, {1, 0}, {0, 6},
  {3, 7}, {3, 5}, {2, 7}, {2, 5}, {1, 7}, {1, 5}, {0, 7},
};

byte shiftRegBinaryValues[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

/**
 * Sets the specified LED indices to ON
 */
void setOnLEDs(int onLedIndices[], int numberIndices) {
  int shiftRegIndex = -1;
  int onLedIndex = -1;
  int pinNumber = -1;

  for (int i = 0; i < numberIndices; i++) {
    onLedIndex = onLedIndices[i];
    if (onLedIndex < 70) {
      shiftRegIndex = mapLedIndexToShiftRegAndPin[onLedIndex][0];
      pinNumber = mapLedIndexToShiftRegAndPin[onLedIndex][1];
      shiftRegBinaryValues[shiftRegIndex] += (1 << pinNumber);
    }
  }
}

/**
 * Turns on the LEDs set to ON previously
 */
void turnOnLEDs() {
  digitalWrite(latchPin, LOW);

  for (int i = 8; i > -1; i--) {
    //    Serial.println(shiftRegBinaryValues[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, shiftRegBinaryValues[i]);
  }

  digitalWrite(latchPin, HIGH);
}

/**
 * Sets all the LEDs OFF
 */
void resetShiftRegBinaryValues() {
  for (int i = 0; i < 9; i++) {
    shiftRegBinaryValues[i] = 0;
  }
}

