#include <Wire.h>
#include <Arduino.h>

#define LCD_ADDRESS 0x27 // Adresa LCD-a na I2C magistrali

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE_BIT 0x04
#define LCD_COMMAND 0x00
#define LCD_DATA 0x01

#define LCD_LINE_1 0x80
#define LCD_LINE_2 0xC0

class LCD_I2C {
public:
  LCD_I2C(uint8_t cols, uint8_t rows);
  void begin();
  void clear();
  void setCursor(uint8_t col, uint8_t row);
  size_t write(uint8_t value);
  void print(const char* str);
  void printAt(uint8_t col, uint8_t row, const char* str);
  void printInt(int value);
  void printFloat(float value, int decimalPlaces);
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void createChar(uint8_t location, uint8_t charmap[]);
private:
  void send(uint8_t value, uint8_t mode);
  void pulseEnable(uint8_t value);
  void write4bits(uint8_t value);
  void expanderWrite(uint8_t value);
  void backlight();
  
  uint8_t _cols;
  uint8_t _rows;
};

LCD_I2C::LCD_I2C(uint8_t cols, uint8_t rows) {
  _cols = cols;
  _rows = rows;
}

void LCD_I2C::begin() {
  Wire.begin();
  backlight();

  // Inicijalizacija LCD-a
  delay(50);
  send(0x03, LCD_COMMAND);
  delay(5);
  send(0x03, LCD_COMMAND);
  delayMicroseconds(100);
  send(0x03, LCD_COMMAND);
  delay(5);
  send(0x02, LCD_COMMAND);
  send(0x20 | (_cols > 1 ? 0x08 : 0x00) | (_rows > 1 ? 0x04 : 0x00), LCD_COMMAND);
  delay(5);

  // Postavljanje parametara prikaza
  clear();
  send(0x06, LCD_COMMAND);
  send(0x0C, LCD_COMMAND);
}

void LCD_I2C::clear() {
  send(0x01, LCD_COMMAND);
  delayMicroseconds(2000);
}

void LCD_I2C::setCursor(uint8_t col, uint8_t row) {
  int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
  if (row >= _rows) {
    row = _rows - 1; // Korekcija neispravnog reda
  }
  send(LCD_LINE_1 + col + row_offsets[row], LCD_COMMAND);
}

size_t LCD_I2C::write(uint8_t value) {
  send(value, LCD_DATA);
  return 1; // Vraćanje broja ispisanog karaktera
}

void LCD_I2C::print(const char* str) {
  while (*str) {
    write(*str);
    str++;
  }
}

void LCD_I2C::printAt(uint8_t col, uint8_t row, const char* str) {
  setCursor(col, row);
  print(str);
}

void LCD_I2C::printInt(int value) {
  char buffer[16];
  sprintf(buffer, "%d", value);
  print(buffer);
}

void LCD_I2C::printFloat(float value, int decimalPlaces) {
  char buffer[16];
  dtostrf(value, 0, decimalPlaces, buffer);
  print(buffer);
}

void LCD_I2C::scrollDisplayLeft() {
  send(0x18, LCD_COMMAND);
}

void LCD_I2C::scrollDisplayRight() {
  send(0x1C, LCD_COMMAND);
}

void LCD_I2C::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x07; // Limitira broj korisničkih karaktera na 8
  send(0x40 | (location << 3), LCD_COMMAND);
  for (int i = 0; i < 8; i++) {
    write(charmap[i]);
  }
}

void LCD_I2C::send(uint8_t value, uint8_t mode) {
  uint8_t highnib = value & 0xF0;
  uint8_t lownib = (value << 4) & 0xF0;
  write4bits(highnib | mode);
  write4bits(lownib | mode);
}

void LCD_I2C::pulseEnable(uint8_t value) {
  expanderWrite(value | LCD_ENABLE_BIT);
  delayMicroseconds(1);
  expanderWrite(value & ~LCD_ENABLE_BIT);
  delayMicroseconds(50);
}

void LCD_I2C::write4bits(uint8_t value) {
  expanderWrite(value);
  pulseEnable(value);
}

void LCD_I2C::expanderWrite(uint8_t value) {
  Wire.beginTransmission(LCD_ADDRESS);
  Wire.write(value | LCD_BACKLIGHT);
  Wire.endTransmission();
}

void LCD_I2C::backlight() {
  expanderWrite(0);
}
