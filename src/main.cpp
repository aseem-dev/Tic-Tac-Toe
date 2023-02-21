#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <ezButton.h>

#define TFT_DC 22
#define TFT_RST 1
#define TFT_CS 3

#define BTN_NXT 33
#define BTN_SLT 25

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

ezButton btnNxt(BTN_NXT);
ezButton btnSlt(BTN_SLT);

char board[3][3];
char players[] = {'X', 'O'};
int row = 0, col = 0;
int player = 0;

void initBoard()
{
  tft.setCursor(30, 15);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_RED);
  tft.print("Tic Tac Toe");

  tft.drawRect(4, 36, 120, 120, ST7735_WHITE);
  tft.drawFastVLine(44, 36, 120, ST7735_WHITE);
  tft.drawFastVLine(84, 36, 120, ST7735_WHITE);
  tft.drawFastHLine(4, 76, 120, ST7735_WHITE);
  tft.drawFastHLine(4, 116, 120, ST7735_WHITE);

  tft.drawRect(9, 41, 31, 31, ST7735_RED);
}

void move()
{
  tft.drawRect(9 + (col * 40), 41 + (row * 40), 31, 31, ST7735_BLACK);
  if (col < 2)
    col++;
  else
  {
    if (row < 2)
      row++;
    else
      row = 0;
    col = 0;
  }
  tft.drawRect(9 + (col * 40), 41 + (row * 40), 31, 31, ST7735_RED);
}

void setup()
{
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  btnNxt.setDebounceTime(50);
  btnSlt.setDebounceTime(50);

  initBoard();
}

void loop()
{
  btnNxt.loop();
  btnSlt.loop();

  if (btnNxt.isReleased())
  {
    move();
  }

  if (btnSlt.isPressed())
  {
    tft.setCursor((col * 40) + 19, (row * 40) + 50);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);
    tft.print(players[player]);
    player = player == 0 ? 1 : 0;
  }
}
