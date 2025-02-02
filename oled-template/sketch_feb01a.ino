#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // пин для ресета

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String inputString = "";
bool newInput = false;

void setup() {
  Serial.begin(9600);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("Failed SSD1306"));
    while (true); 
  }
  //display.clearDisplay();
  display.display(); // по рофлу отображаю лого адафруита
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 32);
  display.print("No available input");
  display.display();
}

void loop() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    // как определять новый инпут хз.
    if (inChar == '\n' || inChar == '\r') {
      newInput = true;
    } else {
      if (newInput) {
        inputString = "";
        newInput = false;
      }
      inputString += inChar;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(inputString);
    display.display();
  }
}
