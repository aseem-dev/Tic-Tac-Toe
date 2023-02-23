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

ezButton btnMove(BTN_NXT);
ezButton btnSelect(BTN_SLT);

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

  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
}

char checkWinner()
{
  for (int i = 0; i < 3; i++)
  {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '\0')
      return board[0][i];
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '\0')
      return board[i][0];
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '\0')
    return board[0][0];
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '\0')
    return board[0][2];
  return '\0';
}

void setup()
{
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  btnMove.setDebounceTime(50);
  btnSelect.setDebounceTime(50);

  initBoard();
}

void loop()
{
  btnMove.loop();
  btnSelect.loop();

  if (btnMove.isPressed())
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

  if (btnSelect.isPressed())
  {
    if (!board[row][col])
    {
      tft.setCursor((col * 40) + 19, (row * 40) + 50);
      board[row][col] = players[player];
      tft.print(players[player]);
      player = player == 0 ? 1 : 0;

      if (char winner = checkWinner())
      {
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(10, 50);
        tft.print("Winner is ");
        tft.setCursor(60, 70);
        tft.println(winner);
      }
    }
  }
}
