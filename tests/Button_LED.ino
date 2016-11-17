const int PIN_LED = 13;
const int PIN_BTN = 9;

int state = HIGH;      // the current state of the output pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers



int buttonState = 0;
boolean isBtnPressed = false;



void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT);
}

void loop() {
  buttonState = digitalRead(PIN_BTN);

  // if the input just went from LOW to HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (buttonState == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }
  

  if(state == HIGH){
    digitalWrite(PIN_LED, HIGH);
  }
  else{
    digitalWrite(PIN_LED, LOW);
  }

  previous = buttonState;

}
