#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Scroller.h" // Calling Scroller Lib

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DSP_ADDR 0x3c
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS DSP_ADDR ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Scroller* scrollers[3];

void setup () {
  Wire.begin(10, 11); // These pins values may vary depending on your device
  Serial.begin(115200);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  // ^^ Initializing Display
  // vv Initializing Scrollers (Scroller(Initial x Value, Final x Value, Y value, Text, display))
  scrollers[0] = new Scroller(0, 128, 11, "fixed line", display);
  scrollers[1] = new Scroller(0, 128, 22, "scrolling line example", display);
  scrollers[2] = new Scroller(64, 128, 33, "further line", display);
  display.display();
}

void loop () {
  display.setCursor(11, 11);
  // vv Calling Scrollers
  scrollers[0]->scrollLine();
  scrollers[1]->scrollLine();
  scrollers[2]->scrollLine();

  // Calling Static fillRect and text after so it doesnt clip
  display.fillRect(0, 33, 64, 11, 0);
  display.setCursor(0, 33);
  display.println("Moving ->");
  //scrollers[3]->scrollLine();
  //scrollers[4]->scrollLine();
  //scrollers[5]->scrollLine();
  display.display();
}