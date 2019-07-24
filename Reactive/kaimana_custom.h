
//  kaimana_custom.h Generated from jasensCustoms.com Kaimana Khameleon Code Generator
//  KK Code Generator: http://brightstick.freecade.org
//  Code is provided for entertainment purposes and use with the Kaimana Khameleon and Panzer Fight Stick 2.
//  Code may be copied, modified, resused with this Copyright notice.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Based on code originally released by ParadiseArcadeShop.com
//  Generator Created:  November 4, 2015    jasenhicks // jasenscustoms.com -- Cavalier Mannitude Encouragement
//
// THIS FILE GENERATED ON: Sunday 19th of August 2018 02:32:12 AM


#ifndef __kaimana_local_h__
#define __kaimana_local_h__
#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"

//ON BUTTON STATE 
#define LED_LEFT_COLOR_ON 63,0,110
#define LED_DOWN_COLOR_ON 63,0,110
#define LED_RIGHT_COLOR_ON 63,0,110
#define LED_UP_COLOR_ON 63,0,110
#define LED_P1_COLOR_ON 0,125,125
#define LED_P2_COLOR_ON 0,125, 125
#define LED_P3_COLOR_ON 0,125, 125
#define LED_P4_COLOR_ON 0,125, 125
#define LED_K1_COLOR_ON 0,144, 72
#define LED_K2_COLOR_ON 0,144, 72
#define LED_K3_COLOR_ON 0,144, 72
#define LED_K4_COLOR_ON 0,144, 72
#define LED_SELECT_COLOR_ON 0,0,0
#define LED_HOME_COLOR_ON 0,0,0
#define LED_START_COLOR_ON 0,0,0


//OFF BUTTON STATE 
#define LED_LEFT_COLOR_OFF 0,0,0
#define LED_DOWN_COLOR_OFF 0,0,0
#define LED_RIGHT_COLOR_OFF 0,0,0
#define LED_UP_COLOR_OFF 0,0,0
#define LED_P1_COLOR_OFF 0,0,0
#define LED_P2_COLOR_OFF 0,0,0
#define LED_P3_COLOR_OFF 0,0,0
#define LED_P4_COLOR_OFF 0,0,0
#define LED_K1_COLOR_OFF 0,0,0
#define LED_K2_COLOR_OFF 0,0,0
#define LED_K3_COLOR_OFF 0,0,0
#define LED_K4_COLOR_OFF 0,0,0
#define LED_SELECT_COLOR_OFF 0,0,0
#define LED_HOME_COLOR_OFF 0,0,0
#define LED_START_COLOR_OFF 0,0,0


//RANDOM COLORS SET
#define COLOR_RANDOM_1 255,0,0
#define COLOR_RANDOM_2 255,255,0
#define COLOR_RANDOM_3 255,255,255
#define COLOR_RANDOM_4 0,0,255
#define COLOR_RANDOM_5 0,255,255
#define COLOR_RANDOM_6 255,0,255
#define COLOR_RANDOM_7 127,255,0
#define COLOR_RANDOM_8 255,0,127
  
//BOOT AND IDLE SEQUENCE TIMING
#define  BOOT_COLOR_DELAY         250
#define  BOOT_COMPLETE_DELAY      500
#define  MAIN_LOOP_DELAY           50
#define IDLE_TIMEOUT_SECONDS       30
#define IDLE_ANIMATION_DELAY       4

//#define BRIGHTNESS                 0.8




//LED INDEX
#define  LED_UP         0
#define  LED_UP_B       1
#define  LED_K1         2
#define  LED_K1_B       3
#define  LED_K2         4
#define  LED_K2_B       5
#define  LED_K3         6
#define  LED_K3_B       7
#define  LED_K4         8
#define  LED_K4_B       9
#define  LED_P4         10
#define  LED_P4_B       11
#define  LED_P3         12
#define  LED_P3_B       13
#define  LED_P2         14    
#define  LED_P2_B       15
#define  LED_P1         16
#define  LED_P1_B       17
#define  LED_RIGHT      18
#define  LED_RIGHT_B    19   
#define  LED_DOWN       20
#define  LED_DOWN_B     21
#define  LED_LEFT       22
#define  LED_LEFT_B     23
#define  LED_SELECT     24
#define  LED_SELECT_B   25
#define  LED_HOME       26
#define  LED_HOME_B     27
#define  LED_START      28
#define  LED_START_B    29

#define  LED_COUNT      30

#endif
