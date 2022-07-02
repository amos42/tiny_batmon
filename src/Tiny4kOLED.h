/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
#ifndef TINY4KOLED_H
#define TINY4KOLED_H

#if defined(TinyWireM_h)
#include "Tiny4kOLED_TinyWireM.h"
#elif defined(TinyI2CMaster_h)
#include "Tiny4kOLED_tiny-i2c.h"
#elif defined(TwoWire_h)
#include "Tiny4kOLED_Wire.h"
#else
#include "Tiny4kOLED_TinyWireM.h"
#endif

#include "Tiny4kOLED_common.h"


/*
class SSD1306Device {
private:

public:
    static inline void sendDataStart(void);
    static inline void sendDataByte(uint8_t byte);
    static inline void sendStop(void);

public:
    // constructor
	SSD1306Device(uint8_t ssd1306_i2c_address, void (*wireBeginFunc)(void), void (*wireBeginTransmissionFunc)(uint8_t ssd1306_i2c_address), bool (*wireWriteFunc)(uint8_t byte), void (*wireEndTransmissionFunc)(void));

    // base api
	void begin(void);
	void begin(uint8_t init_sequence_length, const uint8_t init_sequence []);
	void setFont(const DCfont *font);
    void setCursor(uint8_t x, uint8_t y);
	void clear(void);
	void fill(uint8_t fill);
	void newLine(uint8_t fontHeight);
	void newLine(void);
	size_t write(byte c);
	void bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]);
	void clearToEOL(void);
	void fillToEOL(uint8_t fill);
	void fillLength(uint8_t fill, uint8_t length);
	void startData(void);
	void sendData(const uint8_t data);
	void repeatData(uint8_t data, uint8_t length);
	void clearData(uint8_t length);
	void endData(void);

	// Double Buffering Commands
	void switchRenderFrame(void);
	void switchDisplayFrame(void);
	void switchFrame(void);
	uint8_t currentRenderFrame(void);
	uint8_t currentDisplayFrame(void);

	// 1. Fundamental Command Table
	void setContrast(uint8_t contrast);
	void setEntireDisplayOn(bool enable);
	void setInverse(bool enable);
	void off(void);
	void on(void);

	// 2. Scrolling Command Table
	void scrollRight(uint8_t startPage, uint8_t interval, uint8_t endPage);
	void scrollLeft(uint8_t startPage, uint8_t interval, uint8_t endPage);
	void scrollRightOffset(uint8_t startPage, uint8_t interval, uint8_t endPage, uint8_t offset);
	void scrollLeftOffset(uint8_t startPage, uint8_t interval, uint8_t endPage, uint8_t offset);
	void deactivateScroll(void);
	void activateScroll(void);
	void setVerticalScrollArea(uint8_t top, uint8_t rows);

	// 3. Addressing Setting Command Table
	void setColumnStartAddress(uint8_t startAddress);
	void setMemoryAddressingMode(uint8_t mode);
	void setColumnAddress(uint8_t startAddress, uint8_t endAddress);
	void setPageAddress(uint8_t startPage, uint8_t endPage);
	void setPageStartAddress(uint8_t startPage);

	// 4. Hardware Configuration (Panel resolution and layout related) Command Table
	void setDisplayStartLine(uint8_t startLine);
	void setSegmentRemap(uint8_t remap);
	void setMultiplexRatio(uint8_t mux);
	void setComOutputDirection(uint8_t direction);
	void setDisplayOffset(uint8_t offset);
	void setComPinsHardwareConfiguration(uint8_t alternative, uint8_t enableLeftRightRemap);

	// 5. Timing and Driving Scheme Setting Command table
	void setDisplayClock(uint8_t divideRatio, uint8_t oscillatorFrequency);
	void setPrechargePeriod(uint8_t phaseOnePeriod, uint8_t phaseTwoPeriod);
	void setVcomhDeselectLevel(uint8_t level);
	void nop(void);

	// 6. Advance Graphic Command table
	void fadeOut(uint8_t interval);
	void blink(uint8_t interval);
	void disableFadeOutAndBlinking(void);
	void enableZoomIn(void);
	void disableZoomIn(void);

	// Charge Pump Settings
	void enableChargePump(void);
	void disableChargePump(void);

};
*/

#endif
