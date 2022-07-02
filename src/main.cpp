/**
 * from 2022-07-02 at https://github.com/amos42/tiny_batmon
 */

#include "Tiny4kOLED.h"

// Two included fonts, The space isn't used unless it is needed
#include "font6x8.h"
//#include "font8x16.h"
#include "font8x16digits.h"

SSD1306Device oled(SSD1306);

#define VOLT100 (4.2)
#define VOLT75 (3.76)
#define VOLT50 (3.63)
#define VOLT25 (3.5)
#define VOLT0 (3.2)

const float batteryPercentageTable[][2] = {
    {3.2f, 0},
    {3.5f, 25},
    {3.63f, 50},
    {3.76f, 75},
    {4.2f, 100}};

#define BATTERY_TABLE_SIZE (sizeof(batteryPercentageTable) / (sizeof(float) * 2))

#define ADJUST_VOLT(result) ((result) = (result)*4.0 / 4.2) /// Calibraiton Equation (= result * true Vcc / reading Vcc)

// ============================================================================

float readVcc(void)
{
// Read 1.1V reference against AVcc
// set the reference to Vcc and the measurement to the internal 1.1V reference
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

  delay(2);            // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC))
    ; // measuring

  uint8_t low = ADCL;  // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  float result = (high << 8) | low;
  result = (1.1 * 1023) / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  // ADJUST_VOLT(result);

  return result; // Vcc in millivolts
}

float calcPercentage(float volt)
{
  if (volt < batteryPercentageTable[0][0])
    return 0;
  if (volt >= batteryPercentageTable[BATTERY_TABLE_SIZE - 1][0])
    return batteryPercentageTable[BATTERY_TABLE_SIZE - 1][1];

  float curPerc = 0;
  float curVolt = 0;

  for (unsigned i = 0; i < BATTERY_TABLE_SIZE; i++)
  {
    const float *nextArea = batteryPercentageTable[i];
    if (volt < nextArea[0])
    {
      float vv = (volt - curVolt);
      float dp = (nextArea[1] - curPerc);
      float dv = (nextArea[0] - curVolt);
      curPerc += vv * dp / dv;
      break;
    }
    curPerc = nextArea[1];
    curVolt = nextArea[0];
  }

  return curPerc;
}

void drawBattery(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, int per)
{
  static const uint8_t battery[5][3] = {
      {0xff, 0xff, 0xff},
      {0x01, 0x00, 0x80},
      {0xA1, 0xAA, 0x8A},
      {0x51, 0x55, 0x85},
      {0xff, 0xff, 0xff}};

  int w = x1 - x0 - 2 - 2;
  int w2 = w * per / 100;
  int xx, yy;

  for (uint8_t y = y0; y < y1; y++)
  {
    oled.setCursor(x0, y);
    SSD1306Device::sendDataStart();

    if (y == y0)
      yy = 0;
    else if (y >= y1 - 1)
      yy = 2;
    else
      yy = 1;

    for (uint8_t x = x0; x < x1; x++)
    {
      if (x == x0)
        xx = 0;
      else if (x <= x0 + 2)
        xx = 1;
      else if (x >= x1 - 1)
        xx = 4;
      else if (x >= x1 - 3)
        xx = 1;
      else
      {
        if (x + 3 <= x0 + 3 + w2)
        {
          if (x % 2 > 0)
            xx = 2;
          else
            xx = 3;
        }
        else
        {
          xx = 1;
        }
      }
      SSD1306Device::sendDataByte(battery[xx][yy]);
    }

    SSD1306Device::sendStop();
  }
  oled.setCursor(0, 0);
}

void setup()
{
  // put your setup code here, to run once:

  oled.begin();
  oled.clear();
  oled.on();
}

void loop()
{
  // put your main code here, to run repeatedly:

  float v = readVcc();
  char buf[20];

  int per = (int)calcPercentage(v);

  oled.setCursor(92, 0);
  oled.setFont(FONT8X16DIGITS);

  sprintf(buf, "%3d", per);
  oled.print(buf);

  oled.setFont(FONT6X8);
  oled.setCursor(118, 1);
  oled.write('%');

  oled.setCursor(92, 3);
  dtostrf(v, 4, 2, buf);
  oled.print(buf);
  oled.write('V');

  drawBattery(8, 1, 84, 3, per);

  delay(500);
}
