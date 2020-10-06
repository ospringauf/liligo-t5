#include <Arduino.h>
#include <Wire.h>
// FreeFonts from Adafruit_GFX
// #include <Fonts/FreeMonoBold9pt7b.h>
// #include <Fonts/FreeMonoBold12pt7b.h>
// #include <Fonts/FreeMonoBold18pt7b.h>
// #include <Fonts/FreeMonoBold24pt7b.h>


#define SPI_MOSI 23
#define SPI_MISO -1
#define SPI_CLK 18

#define ELINK_SS 5
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17

#define SDCARD_SS 13
#define SDCARD_CLK 14
#define SDCARD_MOSI 15
#define SDCARD_MISO 2

#define BUTTON_PIN 39

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
// #include <GFX.h>

#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h> // including both doesn't hurt
#include <GxEPD2_3C.h> // including both doesn't hurt
#include <Fonts/FreeMonoBold9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>

// copy constructor for your e-paper from GxEPD2_Example.ino, and for AVR needed #defines
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT> display(GxEPD2_213_B73(/*CS=D8*/ ELINK_SS, /*DC=D3*/ ELINK_DC, /*RST=D4*/ ELINK_RESET, /*BUSY=D2*/ ELINK_BUSY)); 




U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

// void helloWorld()
// {
//   //Serial.println("helloWorld");
//   uint16_t bg = GxEPD_WHITE;
//   uint16_t fg = GxEPD_BLACK;
//   u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
//   u8g2Fonts.setFontDirection(0);            // left to right (this is default)
//   u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
//   u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color
//   u8g2Fonts.setFont(u8g2_font_helvR14_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//   uint16_t x = (display.width() - 160) / 2;
//   uint16_t y = display.height() / 2;
//   display.firstPage();
//   do
//   {
//     display.fillScreen(bg);
//     u8g2Fonts.setCursor(x, y); // start writing at this position
//     u8g2Fonts.print("Hello World!");
//   }
//   while (display.nextPage());
//   //Serial.println("helloWorld done");
// }

// void helloArduino()
// {
//   //Serial.println("helloArduino");
//   uint16_t bg = GxEPD_WHITE;
//   uint16_t fg = GxEPD_BLACK;
//   u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
//   u8g2Fonts.setFontDirection(0);            // left to right (this is default)
//   u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
//   u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color
//   u8g2Fonts.setFont(u8g2_font_helvR14_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//   uint16_t x = (display.width() - 160) / 2;
//   uint16_t y = display.height() / 4;
//   display.setPartialWindow(0, y - 14, display.width(), 20);
//   display.firstPage();
//   do
//   {
//     display.fillScreen(bg);
//     u8g2Fonts.setCursor(x, y);
//     u8g2Fonts.println("Hello Arduino!");
//   }
//   while (display.nextPage());
//   //Serial.println("helloArduino done");
// }

// void helloEpaper()
// {
//   //Serial.println("helloEpaper");
//   uint16_t bg = GxEPD_WHITE;
//   uint16_t fg = GxEPD_BLACK;
//   u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
//   u8g2Fonts.setFontDirection(0);            // left to right (this is default)
//   u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
//   u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color
//   u8g2Fonts.setFont(u8g2_font_helvR14_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//   uint16_t x = (display.width() - 160) / 2;
//   uint16_t y = display.height() * 3 / 4;
//   display.setPartialWindow(0, y - 14, display.width(), 20);
//   display.firstPage();
//   do
//   {
//     display.fillScreen(bg);
//     u8g2Fonts.setCursor(x, y);
//     u8g2Fonts.println("Hello E-Paper!");
//   }
//   while (display.nextPage());
//   //Serial.println("helloEpaper done");
// }


void drawFont(const char name[])
{
  //display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(0, 6);
  u8g2Fonts.println();
  u8g2Fonts.println(name);
  u8g2Fonts.println(" !\"#$%&'()*+,-./");
  u8g2Fonts.println("0123456789:;<=>?");
  u8g2Fonts.println("@ABCDEFGHIJKLMNO");
  u8g2Fonts.println("PQRSTUVWXYZ[\\]^_");
  u8g2Fonts.println("`abcdefghijklmno");
  u8g2Fonts.println("pqrstuvwxyz{|}~ ");
  u8g2Fonts.println("Umlaut ÄÖÜäéöü");
  u8g2Fonts.println("");
  u8g2Fonts.println("The quick brown fox jumps over the lazy cow");
}

void showFont(const char name[], const uint8_t *font)
{
  display.setFullWindow();
  display.setRotation(1);
  u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);              // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  u8g2Fonts.setFont(font); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  display.firstPage();
  do
  {
    drawFont(name);
  }
  while (display.nextPage());
}

// fonts: https://github.com/olikraus/u8g2/wiki/fntlistall

void setup()
{
//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("setup");
  display.init();
  
  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
//   helloWorld();
//   delay(1000);
//   helloArduino();
//   delay(1000);
//   helloEpaper();
//   delay(1000);
  //showFont("u8g2_font_helvR14_tf", u8g2_font_helvR14_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//   showFont("u8g2_font_6x10_tf", u8g2_font_6x10_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//   showFont("u8g2_font_missingplanet_tf", u8g2_font_missingplanet_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
showFont("u8g2_font_BBSesque_tf", u8g2_font_BBSesque_tf); 
}

void loop()
{
}
