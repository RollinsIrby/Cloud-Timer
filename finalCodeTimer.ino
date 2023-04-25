#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip(30, 6, NEO_GRB + NEO_KHZ800);

int buttonPin1 = 7;
int buttonPin2 = 8;

boolean currentState1;
boolean prevState1;

boolean currentState2;
boolean prevState2;

boolean button1Read;
boolean button2Read;

int startTime;
int currentTime;
int interval = 2000;

int count;
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//int lights[] = {1,2,3,4,5,6,7,8,9,10
//};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  strip.begin();
  startTime = millis();
  // set up the LCD's number of columns and rows:

  // Print a message to the LCD.
}

void loop() {
  lcd.begin(16, 2);
  lcd.print(count);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // // print the number of seconds since reset:
  // lcd.print(millis() / 1000);

  strip.setPixelColor(0, 0, 0, 0);
  // 1 button
  button1Read = digitalRead(buttonPin1);

  prevState1 = currentState1;
  currentState1 = debounce(buttonPin1, prevState1);

  //10 button
  button2Read = digitalRead(buttonPin2);

  prevState2 = currentState2;
  currentState2 = debounce(buttonPin2, prevState2);

  if (button1Read == true && prevState1 == false) {
    count += 1;
    startTime = millis();
  }
  if (button2Read == true && prevState2 == false) {
    count += 10;
    startTime = millis();
  }



  if (millis() - startTime >= interval) {
    count -= 1;
    startTime = millis();
  }

  if (count > 30) {
    count = 30;
  }


  strip.clear();
  for (int i = 0; i < count; i++) {
    strip.setBrightness(50);
    strip.setPixelColor(i, 152, 235, 136);
    strip.show();
  }


  if (count <= 0) {
    count = 0;
    if (count == 0) {
      strip.clear();
      strip.show();
    }
  }

  Serial.println(count);
}



boolean debounce(int aButPin, int aPrevState) {

  // bouncy reading
  boolean aButState = digitalRead(aButPin);

  // if you just pressed the button, wait
  // debounces the signal
  if (aButState == HIGH && aPrevState == LOW) {
    delay(15);
  }

  // return results
  return aButState;
}
