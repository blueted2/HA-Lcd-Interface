#include <U8g2lib.h>

#define phase1_width 28
#define phase1_height 10
static unsigned char phase1[] U8X8_PROGMEM = {
    0x00,
    0x00,
    0x00,
    0x00,
    0xE0,
    0x00,
    0x38,
    0x00,
    0x10,
    0x01,
    0x44,
    0x00,
    0x08,
    0x02,
    0x82,
    0x00,
    0x08,
    0x02,
    0x82,
    0x00,
    0x04,
    0x04,
    0x01,
    0x01,
    0x04,
    0x04,
    0x01,
    0x01,
    0x02,
    0x88,
    0x00,
    0x02,
    0x01,
    0x70,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x00,
};

#define phase2_width 28
#define phase2_height 10
static unsigned char phase2[] U8X8_PROGMEM = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x1C,
    0x00,
    0x03,
    0x00,
    0x22,
    0x80,
    0x00,
    0x01,
    0x41,
    0x40,
    0x00,
    0x01,
    0x41,
    0x40,
    0x00,
    0x82,
    0x80,
    0x20,
    0x00,
    0x82,
    0x80,
    0x20,
    0x00,
    0x44,
    0x00,
    0x11,
    0x00,
    0x38,
    0x00,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

#define car_width 39
#define car_height 15
static unsigned char car[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 
  0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x7F};


#define car_charging_width 39
#define car_charging_height 15
static unsigned char car_charging[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 
  0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x7F};