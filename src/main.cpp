#include <Arduino.h>
#include <Wire.h>

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

// SD
// has support for FAT32 support with long filenames
#include "FS.h"
#include "SD.h"
#include "SPI.h"

SPIClass sdSPI(VSPI);
//#define SdFile File

// copy constructor for your e-paper from GxEPD2_Example.ino, and for AVR needed #defines
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))

GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT> display(GxEPD2_213_B73(/*CS=D8*/ ELINK_SS, /*DC=D3*/ ELINK_DC, /*RST=D4*/ ELINK_RESET, /*BUSY=D2*/ ELINK_BUSY)); 

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
bool sdOK = false;

// fonts: https://github.com/olikraus/u8g2/wiki/fntlistall

const uint8_t* font = 
  // u8g2_font_t0_11_mf
  u8g2_font_t0_13_mf
  // u8g2_font_BBSesque_tf  
  // u8g2_font_prospero_bold_nbp_tf
  // u8g2_font_unifont_tf
  ;

const uint8_t* font2 = 
  u8g2_font_open_iconic_thing_4x_t
;


void helloWorld()
{
  display.setFullWindow();
  display.setRotation(1);

  u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);              // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  u8g2Fonts.setFont(font); 

//   display.setFont(&FreeMonoBold9pt7b);

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    u8g2Fonts.setCursor(4, 8);
    u8g2Fonts.println();
    u8g2Fonts.println("HELLO WORLD______________");
    u8g2Fonts.println();
    u8g2Fonts.println("The quick brown fox jumps");
    u8g2Fonts.println("over the lazy cow");
    u8g2Fonts.println();

    if (sdOK) {
        uint32_t cardSize = SD.cardSize() / (1024 * 1024);
        u8g2Fonts.println("SDCard: " + String(cardSize) + "MB");
    } else {
        u8g2Fonts.println("SDCard  None");
    }
    
    u8g2Fonts.setFont(font2); 
    u8g2Fonts.setCursor(150, 110);
    u8g2Fonts.println("D E M");



    // display.setCursor(2, 8);
    // display.setTextColor(GxEPD_BLACK);
    // display.println("HELLO WORLD");
    // display.println("The quick brown fox jumps over the lazy cow");

    // max visible rect on 213B73 display
    // display.drawRect(0, 6, 250, 122,GxEPD_BLACK);
  }
  while (display.nextPage());
}

void setup()
{
    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);

    if (!SD.begin(SDCARD_SS, sdSPI)) {
        sdOK = false;
    } else {
        sdOK = true;
    }

  display.init();
  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX

  helloWorld();
  display.hibernate();
}

void loop() {};