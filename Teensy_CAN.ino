#include <FlexCAN.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


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

static CAN_message_t msg,rxmsg;
volatile uint32_t count = 0;
IntervalTimer TX_timer;
String CANStr(""); 
volatile uint32_t can_msg_count = 0;
int lastID = 123;//Sist ID 

void setup() {
  Serial.begin(9600);
  Can0.begin(500000); //set speed here.

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
  display.write("CAN-statistikk");

//Dotted line
  display.drawLine(10, 22, 15, 22, WHITE);
  display.drawLine(20, 22, 25, 22, WHITE);
  display.drawLine(30, 22, 35, 22, WHITE);
  display.drawLine(40, 22, 45, 22, WHITE);
  display.drawLine(50, 22, 55, 22, WHITE);
  display.drawLine(60, 22, 65, 22, WHITE);

  display.setCursor(10, 25);
  display.write("Motatt:");

   display.setCursor(10, 35);
  display.write("Sist ID:");

//Dotted line
   display.drawLine(10, 45, 15, 45, WHITE);
  display.drawLine(20, 45, 25, 45, WHITE);
  display.drawLine(30, 45, 35, 45, WHITE);
  display.drawLine(40, 45, 45, 45, WHITE);
  display.drawLine(50, 45, 55, 45, WHITE);
  display.drawLine(60, 45, 65, 45, WHITE);

  msg.buf[0] = 1;
  msg.buf[1] = 2;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.len = 8;
  msg.id = 0x7DF;
  msg.flags.extended = 0; 
  msg.flags.remote = 0;
//  msg.timeout = 500;
  TX_timer.begin(tx_CAN, 1000000);    /* Start interrutp timer */
}

void tx_CAN(void)
{
  msg.len = 8;
  msg.id = 0x7DF;
  msg.buf[0] = 0x02;
  msg.buf[1] = 0x01;
  msg.buf[2] = 0x0c;
  msg.buf[3] = 0;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;
  /*
  msg.buf[4] = can_msg_count >> 24;
  msg.buf[5] = can_msg_count >> 16;
  msg.buf[6] = can_msg_count >> 8;
  msg.buf[7] = can_msg_count;
  */
  Can0.write(msg);
  can_msg_count++;
}

void loop() {

  display.fillRect(60, 25, 53, 20, BLACK);//Klarer begrenset området 
  
//Display message count
  display.setCursor(60, 25);
  display.print(can_msg_count);

//Display last ID
  display.setCursor(60, 35);
  display.print(lastID);

  display.display();

  while(Can0.read(rxmsg))
  { 
     String CANStr(""); 
     for (int i=0; i < 8; i++) {     

         CANStr += String(rxmsg.buf[i],HEX);
         CANStr += (" ") ;
     }
     Serial.print(rxmsg.id,HEX); 
     Serial.print(' '); 
     Serial.print(rxmsg.len,HEX); 
     Serial.print(' ');
     Serial.println(CANStr);  
     
     display.fillRect(0,15,128, 30,BLACK);
     display.setCursor(0,15);
     
     display.println(rxmsg.id,HEX); 
     display.println(rxmsg.len,HEX); 
     display.println(CANStr);
     display.display();

     
  }

  delay(50);
  
}


