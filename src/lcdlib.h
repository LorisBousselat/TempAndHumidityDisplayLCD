#include <LiquidCrystal_I2C.h>
#include <string>

const int nbColumns = 16;
const int nbRows = 2;

LiquidCrystal_I2C lcd(0x27, nbColumns, nbRows); // set the LCD address to 0x27 for a 16 chars and 2 line display

void scrollMessage(int row, String message, int delayTime);
void fulFillWithBlank(String &message);
void printLCD(int row, int col, String message);

void setLcd()
{
    lcd.init();      // initialize the lcd
    lcd.backlight(); // Turns on the LCD backlight.
    scrollMessage(0, "Temperature and humidity...", 500);
}

void clearLCD()
{
    lcd.clear();
}

void printLCD(int row, int col, String message)
{
    lcd.setCursor(col, row);
    lcd.print(message);
}

void fulFillWithBlank(String &message)
{
    for (int i = 0; i <= nbColumns - message.length(); i++)
    {
        message.concat(" ");
    }
}

void scrollMessage(int row, String message, int delayTime)
{
    int size = message.length();
    String toPrint = "";

    // The message will parade
    for (int position = 0; position < size; position++)
    {
        // the portion that can be displayed
        toPrint = message.substring(position, position + nbColumns);
        // print " " for lasting space in the screen
        if (toPrint.length() < nbColumns)
        {
            fulFillWithBlank(toPrint);
        }
        lcd.setCursor(0, row);
        lcd.print(toPrint);

        delay(delayTime);
    }
}