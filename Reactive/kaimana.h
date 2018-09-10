//  kaimana.h
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana class based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#ifndef __kaimana_h__
#define __kaimana_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana_custom.h"

#define  BLACK    000,000,000
#define  RED      255,000,000
#define  GREEN    000,255,000
#define  YELLOW   255,255,000
#define  BLUE     000,000,255
#define  PURPLE   255,000,255
#define  CYAN     000,255,255
#define  WHITE    255,255,255
      

// Map function names to arduino leonardo atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  PIN_DOWN    11   //PB7
#define  PIN_UP      18   //PF7
#define  PIN_LEFT    19   //PF6
#define  PIN_RIGHT   20   //PF5
#define  PIN_SELECT  9    //PB5
#define  PIN_HOME    8    //PB4
#define  PIN_START   10   //PB6
#define  PIN_P1      3    //PD0
#define  PIN_P2      2    //PD1
#define  PIN_P3      0    //PD2
#define  PIN_P4      1    //PD3
#define  PIN_K1      4    //PD4
#define  PIN_K2      21   //PF4
#define  PIN_K3      12   //PD6
#define  PIN_K4      6    //PD7
//
#define  PIN_LED     23


// Map function names to binary input masks on atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  ATTACK_UP      0x0800UL
#define  ATTACK_DOWN    0x0400UL
#define  ATTACK_LEFT    0x0200UL
#define  ATTACK_RIGHT   0x0100UL
#define  ATTACK_K4      0x0080UL
#define  ATTACK_K3      0x0040UL
#define  ATTACK_K2      0x0020UL
#define  ATTACK_K1      0x0010UL
#define  ATTACK_P4      0x0008UL
#define  ATTACK_P3      0x0004UL
#define  ATTACK_P2      0x0002UL
#define  ATTACK_P1      0x0001UL
#define  ATTACK_NONE    0x0000UL
#define  ATTACK_FALSE   0xFFFFUL


// number of switch inputs on kaimana
#define  SWITCH_COUNT         15

// if this is changed then Kaimana::switchHistoryTest must also be revised
#define SWITCH_HISTORY_MAX  16

// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;


// table of switch pin numbers
const unsigned char switchPins[SWITCH_COUNT] = { PIN_DOWN, PIN_UP, PIN_LEFT, PIN_RIGHT, PIN_HOME, PIN_SELECT, PIN_START, PIN_P1, PIN_P2, PIN_P3, PIN_P4, PIN_K1, PIN_K2, PIN_K3, PIN_K4 };


// define the Kaimana class
//
class Kaimana
{
  private:
    // declare RGB array for 15 buttons --> 12 LEDs
    // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
    RGB_t    _led[LED_COUNT];
    uint16_t _switchHistory[SWITCH_HISTORY_MAX];

  public:
    Kaimana(void);
    void    setLED(int index, int iR, int iG, int iB, float BRIGHTNESS);
    void    setALL(int iR, int iG, int iB);
    void    updateALL(void);
    void    switchHistoryClear(void);
    void    switchHistorySet(uint16_t latestValue);
    boolean switchHistoryTest( uint16_t a0=ATTACK_FALSE, uint16_t a1=ATTACK_FALSE, uint16_t a2=ATTACK_FALSE,  uint16_t a3=ATTACK_FALSE,  uint16_t a4=ATTACK_FALSE,  uint16_t a5=ATTACK_FALSE,  uint16_t a6=ATTACK_FALSE,  uint16_t a7=ATTACK_FALSE, uint16_t a8=ATTACK_FALSE, uint16_t a9=ATTACK_FALSE, uint16_t a10=ATTACK_FALSE, uint16_t a11=ATTACK_FALSE, uint16_t a12=ATTACK_FALSE, uint16_t a13=ATTACK_FALSE, uint16_t a14=ATTACK_FALSE, uint16_t a15=ATTACK_FALSE );
};


// prototypes for Kaimana functions
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
void 	setLED(int index, int iR, int iG, int iB, float BRIGHTNESS);
void 	setALL(int iR, int iG, int iB);
void 	updateALL(void);
void 	switchHistoryClear(void);
void 	switchHistorySet(uint16_t latestValue);
boolean switchHistoryTest( uint16_t a0=ATTACK_FALSE, uint16_t a1=ATTACK_FALSE, uint16_t a2=ATTACK_FALSE,  uint16_t a3=ATTACK_FALSE,  uint16_t a4=ATTACK_FALSE,  uint16_t a5=ATTACK_FALSE,  uint16_t a6=ATTACK_FALSE,  uint16_t a7=ATTACK_FALSE, uint16_t a8=ATTACK_FALSE, uint16_t a9=ATTACK_FALSE, uint16_t a10=ATTACK_FALSE, uint16_t a11=ATTACK_FALSE, uint16_t a12=ATTACK_FALSE, uint16_t a13=ATTACK_FALSE, uint16_t a14=ATTACK_FALSE, uint16_t a15=ATTACK_FALSE );

//Definitions for combo switch patterns
//Test for switches in reverse order (newest to oldest)
//   street figher 4 - ryu's special moves
//   http://www.eventhubs.com/guides/2008/jul/06/ryu-street-fighter-4-character-guide/
//
#define  COMBO_PATTERN_1A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_1B    ATTACK_RIGHT + ATTACK_P2, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_2A    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P1, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_2B    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P2, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_3A    ATTACK_LEFT + ATTACK_K1, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_3B    ATTACK_LEFT + ATTACK_K2, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_4A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_5A    ATTACK_RIGHT + ATTACK_P3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_6A    ATTACK_RIGHT + ATTACK_K3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN


// data points for single full sinusoidal wave _/-\_/-
//
const prog_uint8_t sinusoid[257] PROGMEM = {
  0, 3, 6, 9, 12, 15, 18, 21, 24, 28, 31, 34, 37, 40, 43, 46, 49, 52,
  55, 58, 61, 64, 68, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97, 100, 103,
  106, 109, 111, 114, 117, 120, 122, 125, 128, 131, 133, 136, 139, 141,
  144, 146, 149, 151, 154, 156, 159, 161, 164, 166, 168, 171, 173, 175,
  178, 180, 182, 184, 186, 188, 191, 193, 195, 197, 199, 201, 202, 204,
  206, 208, 210, 212, 213, 215, 217, 218, 220, 221, 223, 224, 226, 227,
  229, 230, 231, 233, 234, 235, 236, 237, 239, 240, 241, 242, 243, 244,
  244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 251, 252, 252, 253,
  253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254,
  254, 254, 254, 253, 253, 253, 252, 252, 251, 251, 250, 250, 249, 248,
  248, 247, 246, 245, 244, 244, 243, 242, 241, 240, 239, 237, 236, 235,
  234, 233, 231, 230, 229, 227, 226, 224, 223, 221, 220, 218, 217, 215,
  213, 212, 210, 208, 206, 204, 202, 201, 199, 197, 195, 193, 191, 188,
  186, 184, 182, 180, 178, 175, 173, 171, 168, 166, 164, 161, 159, 156,
  154, 151, 149, 146, 144, 141, 139, 136, 133, 131, 128, 125, 122, 120,
  117, 114, 111, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 77,
  74, 71, 68, 64, 61, 58, 55, 52, 49, 46, 43, 40, 37, 34, 31, 28, 24,
  21, 18, 15, 12, 9, 6, 3, 0
};


// data points for color cycling
//
const prog_uint8_t colorCycleData[] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   2,   4,   6,   8,  10,  12,  14,  16,  18,  20,  22,  24,  26,  28,  30,
   32,  35,  38,  41,  44,  47,  50,  53,  56,  59,  62,  65,  68,  71,  74,  77,
   81,  85,  89,  93,  97, 101, 105, 109, 113, 117, 121, 125, 129, 133, 137, 141,
  148, 155, 162, 169, 176, 183, 190, 197, 204, 211, 218, 225, 232, 239, 246, 253,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  253, 246, 239, 232, 225, 218, 211, 204, 197, 190, 183, 176, 169, 162, 155, 148,
  141, 137, 133, 129, 125, 121, 117, 113, 109, 105, 101,  97,  93,  89,  85,  81,
   77,  74,  71,  68,  65,  62,  59,  56,  53,  50,  47,  44,  41,  38,  35,  32,
   30,  28,  26,  24,  22,  20,  18,  16,  14,  12,  10,   8,   6,   4,   2,   0
};

#endif

