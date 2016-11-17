/**
 * Basic implementation of Connect Four, with two human players.
 */

int latchPin = 12;
int clockPin = 13;
int dataPin = 11;
int arrColBtnPins[] = { 2, 3, 4, 5, 6, 7, 8 };
int btnStartPin = 9;
int unusedPin = 0;

boolean gameStart = false;
boolean redTurn = false; // When game is started, if redTurn is false, it is yellow's turn

long randomNumber;

int gameBoard[35]; // 0 for empty, 1 for red, 2 for yellow

int arrayWinningIndices[4];

void setup() {
  Serial.begin(9600);

  // OUTPUT PINS
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // INPUT PINS
  for (int i = 0; i < 7; i++) {
    pinMode(arrColBtnPins[i], INPUT);
  }
  pinMode(btnStartPin, INPUT);

  randomSeed(analogRead(0));

  resetShiftRegBinaryValues();
  turnOnLEDs();
}

boolean gameWon = false;
int winner = 0;

void resetArrays() {
  for (int i = 0; i < 35; i++) {
    gameBoard[i] = 0;
  }
  resetShiftRegBinaryValues();
}

void loop() {
  if (!gameStart) {
    if (digitalRead(btnStartPin) == HIGH) {
      resetArrays();
      randomizeFirstTurn();
      Serial.println("GAME STARTED");
    }
  }
  else if (gameWon) {
    victoryFlash(winner, 4);
    gameStart = false;
    gameWon = false;
  }
  else {
    if (digitalRead(btnStartPin) == HIGH) {
      gameStart = false;
      gameWon = false;
    }
    int checkWin = isGameWon();
    if (checkWin > 0) {
      Serial.println("VICTORY");
      gameWon = true;
      winner = checkWin;
    }
    else {
      for (int i = 0; i < 7; i++) {
        if (digitalRead(arrColBtnPins[i]) == HIGH) {
          if (placePieceInColumn(i)) {
            redTurn = !redTurn;
          }
          else {
            displayInvalidMove();
          }
        }
      }
    }
  }
}

void displayInvalidMove() {
  // Show that move is invalid
}

boolean toggleWinLights = false;

void victoryFlash(int color, int flashes) {
  int arrOnLeds[4];
  boolean toggleFlashLights = true;

  for (int k = 0; k < flashes * 2; k++) {
    resetShiftRegBinaryValues();

    if (toggleFlashLights) {
      int i;

      for (int j = 0; j < 4; j++) {
        i = arrayWinningIndices[j];
        if (color == 1) { // Red flash
          arrOnLeds[j] = i + (i / 7) * 7;
        }
        else { // Yellow flash
          arrOnLeds[j] = i + 7 + (i / 7) * 7;
        }
      }

      setOnLEDs(arrOnLeds, 4);

    }

    turnOnLEDs();

    delay(100);

    toggleFlashLights = !toggleFlashLights;

  }

}

void flash(int color, int flashes) {
  int arrOnLeds[35];
  boolean toggleFlashLights = true;

  for (int i = 0; i < flashes * 2; i++) {
    resetShiftRegBinaryValues();

    if (toggleFlashLights) {

      for (int i = 0; i < 35; i++) {
        if (color == 1) { // Red flash
          arrOnLeds[i] = i + (i / 7) * 7;
        }
        else { // Yellow flash
          arrOnLeds[i] = i + 7 + (i / 7) * 7;
        }
      }

      setOnLEDs(arrOnLeds, 35);

    }

    turnOnLEDs();

    delay(100);

    toggleFlashLights = !toggleFlashLights;

  }

}


void randomizeFirstTurn() {
  randomNumber = random(2); // random number, either 0 or 1
  if (randomNumber == 0) {
    redTurn = true;
  }
  else {
    redTurn = false;
  }
  flash(randomNumber + 1, 2);
  gameStart = true;
}

/**
 * Returns true if the move is valid.
 */
boolean placePieceInColumn(int colIndex) {
  boolean invalidColumn = false;
  int leftmostSpot = 28;
  int spot = leftmostSpot + colIndex;
  boolean isSpotTaken = (gameBoard[spot] != 0);
  while (isSpotTaken && !invalidColumn) {
    spot -= 7;
    isSpotTaken = (gameBoard[spot] != 0);
    if (spot < 0) {
      invalidColumn = true;
      return false;
    }
  }
  placePieceAtSpot(spot);
  return true;
}

void placePieceAtSpot(int spot) {
  if (redTurn) {
    gameBoard[spot] = 1;
    int ledIndex = spot + ( (spot / 7) * 7 ); // convert spot to LED index
    int arrLedIndex[] = { ledIndex };
    setOnLEDs(arrLedIndex, 1);
  }
  else {
    gameBoard[spot] = 2;
    int ledIndex = spot + 7 + ( (spot / 7) * 7 ); // convert spot to LED index
    int arrLedIndex[] = { ledIndex };
    setOnLEDs(arrLedIndex, 1);
  }
  turnOnLEDs();
  delay(300);
}

int diagonalArray1[5][5] = {
  {3, 9, 15, 21, -1},
  {4, 10, 16, 22, 28},
  {5, 11, 17, 23, 29},
  {6, 12, 18, 24, 30},
  {13, 19, 25, 31, -1}
};

int diagonalArray2[5][5] = {
  {3, 11, 19, 27, -1},
  {2, 10, 18, 26, 34},
  {1, 9, 17, 25, 33},
  {0, 8, 16, 24, 32},
  {7, 15, 23, 31, -1}
};

int isGameWon() {
  int redPiecesInARow = 0;
  int yellowPiecesInARow = 0;

  // Check rows
  for (int i = 0; i < 35; i++) {
    if (i % 7 == 0) {
      redPiecesInARow = 0;
      yellowPiecesInARow = 0;
    }
    if (gameBoard[i] == 1) {
      arrayWinningIndices[redPiecesInARow] = i;
      redPiecesInARow++;
      if (yellowPiecesInARow > 0) {
        yellowPiecesInARow = 0;
      }
    }
    else if (gameBoard[i] == 2) {
      arrayWinningIndices[yellowPiecesInARow] = i;
      yellowPiecesInARow++;
      if (redPiecesInARow > 0) {
        redPiecesInARow = 0;
      }
    }
    else {
      redPiecesInARow = 0;
      yellowPiecesInARow = 0;
    }
    if (redPiecesInARow == 4) {
      return 1;
    }
    if (yellowPiecesInARow == 4) {
      return 2;
    }
  }

  // Check columns
  for (int i = 0; i >= 0 ; ) {
    if (i < 7) {
      redPiecesInARow = 0;
      yellowPiecesInARow = 0;
    }
    if (gameBoard[i] == 1) {
      arrayWinningIndices[redPiecesInARow] = i;
      redPiecesInARow++;
      if (yellowPiecesInARow > 0) {
        yellowPiecesInARow = 0;
      }
    }
    else if (gameBoard[i] == 2) {
      arrayWinningIndices[yellowPiecesInARow] = i;
      yellowPiecesInARow++;
      if (redPiecesInARow > 0) {
        redPiecesInARow = 0;
      }
    }
    else {
      redPiecesInARow = 0;
      yellowPiecesInARow = 0;
    }
    if (redPiecesInARow == 4) {
      return 1;
    }
    if (yellowPiecesInARow == 4) {
      return 2;
    }
    if (i == 34) {
      i = -1;
    }
    else if (i != 27) {
      i = (i + 7) % 34;
    }
    else {
      i = 34;
    }
  }

  // Check first diagonals
  for (int i = 0; i < 5; i++) {
    int index;
    redPiecesInARow = 0;
    yellowPiecesInARow = 0;
    for (int j = 0; j < 5; j++) {
      index = diagonalArray1[i][j];
      if (gameBoard[index] == 1) {
        arrayWinningIndices[redPiecesInARow] = index;
        redPiecesInARow++;
        if (yellowPiecesInARow > 0) {
          yellowPiecesInARow = 0;
        }
      }
      else if (gameBoard[index] == 2) {
        arrayWinningIndices[yellowPiecesInARow] = index;
        yellowPiecesInARow++;
        if (redPiecesInARow > 0) {
          redPiecesInARow = 0;
        }
      }
      else {
        redPiecesInARow = 0;
        yellowPiecesInARow = 0;
      }
      if (redPiecesInARow == 4) {
        return 1;
      }
      if (yellowPiecesInARow == 4) {
        return 2;
      }
    }
  }

  // Check second diagonals
  for (int i = 0; i < 5; i++) {
    int index;
    redPiecesInARow = 0;
    yellowPiecesInARow = 0;
    for (int j = 0; j < 5; j++) {
      index = diagonalArray2[i][j];
      if (gameBoard[index] == 1) {
        arrayWinningIndices[redPiecesInARow] = index;
        redPiecesInARow++;
        if (yellowPiecesInARow > 0) {
          yellowPiecesInARow = 0;
        }
      }
      else if (gameBoard[index] == 2) {
        arrayWinningIndices[yellowPiecesInARow] = index;
        yellowPiecesInARow++;
        if (redPiecesInARow > 0) {
          redPiecesInARow = 0;
        }
      }
      else {
        redPiecesInARow = 0;
        yellowPiecesInARow = 0;
      }
      if (redPiecesInARow == 4) {
        return 1;
      }
      if (yellowPiecesInARow == 4) {
        return 2;
      }
    }
  }
  return 0;
}

void redVictory() {

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
