#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ADXL335.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define zPort 26
ADXL335 acelerometro(A9, A8, A7);


// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    6
#define OLED_CS    10
#define OLED_RESET 5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

void setup() {
  Serial.begin(9600);

  pinMode(zPort, OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(1000);


  display.display();
  // Clear the buffer
  delay(1000);
  display.clearDisplay();

//Interface setup
  display.display();
  display.drawRect(1, 1,127, 63, WHITE);
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(10, 3);
  display.write("MAS245 - Gruppe 7");

//Obligatorisk linje
  display.drawLine(10, 11, 118, 11, WHITE);

  display.setCursor(10, 13);
  display.write("IMU data");

//Dotted line
  display.drawLine(10, 22, 15, 22, WHITE);
  display.drawLine(20, 22, 25, 22, WHITE);
  display.drawLine(30, 22, 35, 22, WHITE);
  display.drawLine(40, 22, 45, 22, WHITE);
  display.drawLine(50, 22, 55, 22, WHITE);
  display.drawLine(60, 22, 65, 22, WHITE);

  display.setCursor(10, 25);
  display.write("X-IMU:");

   display.setCursor(10, 35);
  display.write("Y-IMU:");

     display.setCursor(10, 45);
  display.write("Z-IMU:");

//Dotted line
   display.drawLine(10, 55, 15, 55, WHITE);
  display.drawLine(20, 55, 25, 55, WHITE);
  display.drawLine(30, 55, 35, 55, WHITE);
  display.drawLine(40, 55, 45, 55, WHITE);
  display.drawLine(50, 55, 55, 55, WHITE);
  display.drawLine(60, 55, 65, 55, WHITE);

  analogReference(EXTERNAL);
  acelerometro.preset();

  
}

void loop() {
  float xG = acelerometro.getGX();//Hent X data, verdi i G-krefter
  float yG = acelerometro.getGY();//Hent Y data, verdi i G-krefter
  float zG = acelerometro.getGZ();//Hent Z data, verdi i G-krefter

  display.fillRect(50, 25, 53, 30, BLACK);//Klarer begrenset området 
  
//Display X data
  display.setCursor(50, 25);
  display.print(3.5+xG*9.81);//Kalibrering(+3.5) og konvertering til m/s^2
  display.setCursor(85, 25);
  display.print("m/s^2");

//Display Y data
  display.setCursor(50, 35);
  display.print(7.94+yG*9.81);//Kalibrering(+7.94) og konvertering til m/s^2
  display.setCursor(85, 35);
  display.print("m/s^2");

//Display Z data
  display.setCursor(50, 45);
  display.print(3.4+zG*9.81);//Kalibrering(+3.4) og konvertering til m/s^2
  display.setCursor(85, 45);
  display.print("m/s^2");
  display.display();
  delay(50);
  
}


