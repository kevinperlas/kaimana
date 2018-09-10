//  Reactive.ino
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
//  Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//


#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);

// Global Brightness Variables
float BRIGHTNESS_UP ;
float BRIGHTNESS_RIGHT ;
float BRIGHTNESS_DOWN ;
float BRIGHTNESS_LEFT ;
float BRIGHTNESS_K1 ;
float BRIGHTNESS_K2 ;
float BRIGHTNESS_K3 ;
float BRIGHTNESS_K4 ;
float BRIGHTNESS_P1 ;
float BRIGHTNESS_P2 ;
float BRIGHTNESS_P3 ;
float BRIGHTNESS_P4 ;


// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
  showStartup();
}


// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  uint8_t i;

  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );


  // infinite loop of read switches, update LEDs and idle animation when necessary
  while(true)
  {
    // active -- poll switches and update leds
    if( pollSwitches() != 0 )
    {
        // some switches were active so reset idle timeout to now + some seconds
        ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
    }
    else
    {
        // no switches active so test for start of idle timeout  
        if( millis() > ulTimeout )
        {
          animation_idle();
        }  
    }
    
    
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    delay( MAIN_LOOP_DELAY );
  } 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================


// light up all leds at boot to demonstrate everything is functional
//
void showStartup(void)
{
  kaimana.setALL( BLACK );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( RED );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( GREEN );
  delay( BOOT_COLOR_DELAY );
  kaimana.setALL( BLUE );
  delay( BOOT_COLOR_DELAY );

  kaimana.setALL( BLACK );
  delay( BOOT_COMPLETE_DELAY );
} 


// set LED to one of 8 predefined colors selected at random
// I'm not messing with random colors for fading so whatever
void setLEDRandomColor(int index)
{
  switch(random(1,8))    // pick a random color between 1 and 8
  {
    case 1:
      kaimana.setLED(index, COLOR_RANDOM_1, 1);
      break;
    case 2:
      kaimana.setLED(index, COLOR_RANDOM_2, 1);
      break;
    case 3:
      kaimana.setLED(index, COLOR_RANDOM_3, 1);
      break;
    case 4:
      kaimana.setLED(index, COLOR_RANDOM_4, 1);
      break;
    case 5:
      kaimana.setLED(index, COLOR_RANDOM_5, 1);
      break;
    case 6:
      kaimana.setLED(index, COLOR_RANDOM_6, 1);
      break;
    case 7:
      kaimana.setLED(index, COLOR_RANDOM_7, 1);
      break;
    case 8:
      kaimana.setLED(index, COLOR_RANDOM_8, 1);
      break;
    default:   // any undefined value so discard data and set led to BLACK
      kaimana.setLED(index, BLACK, 1);    
      break;
  }  
}



int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  joystickDirection = ATTACK_NONE;
  
  if(!digitalRead(PIN_RIGHT))
  {
    switchActivity |= ATTACK_RIGHT;
    
    // switch is active
    if(iLED[LED_RIGHT] == true)
    {
      //maintain color while switch is active
      iLED[LED_RIGHT] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_RIGHT_ON      
        setLEDRandomColor(LED_RIGHT);  
      #else
         kaimana.setLED(LED_RIGHT, LED_RIGHT_COLOR_ON, 1);
         BRIGHTNESS_RIGHT = 1;        
      #endif
      iLED[LED_RIGHT] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_RIGHT > 0.12)
    {
      BRIGHTNESS_RIGHT = BRIGHTNESS_RIGHT / 1.2 ;
    }
    kaimana.setLED(LED_RIGHT, LED_RIGHT_COLOR_ON, BRIGHTNESS_RIGHT);
    iLED[LED_RIGHT] = false;
  }
  
    if(!digitalRead(PIN_LEFT))
  {
    switchActivity |= ATTACK_LEFT;
    
    // switch is active
    if(iLED[LED_LEFT] == true)
    {
      //maintain color while switch is active
      iLED[LED_LEFT] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_LEFT_ON      
        setLEDRandomColor(LED_LEFT);  
      #else
         kaimana.setLED(LED_LEFT, LED_LEFT_COLOR_ON,1);
         BRIGHTNESS_LEFT = 1;      
      #endif
      iLED[LED_LEFT] = true;
    }
  }
  else
  {
    // switch is inactive
    if (BRIGHTNESS_LEFT > 0.12)
    {
      BRIGHTNESS_LEFT = BRIGHTNESS_LEFT / 1.2 ;
      kaimana.setLED(LED_LEFT, LED_LEFT_COLOR_ON, BRIGHTNESS_LEFT);
    }
    else
    {
      kaimana.setLED(LED_LEFT, BLACK, 1);
    }
    iLED[LED_LEFT] = false;
  }

  if(!digitalRead(PIN_UP))
  {
    switchActivity |= ATTACK_UP;
    // switch is active
    if(iLED[LED_UP] == true)
    {
      //maintain color while switch is active
      iLED[LED_UP] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_UP_ON      
        setLEDRandomColor(LED_UP);  
      #else
         kaimana.setLED(LED_UP, LED_UP_COLOR_ON, 1);
         BRIGHTNESS_UP = 1;
      #endif
      iLED[LED_UP] = true;
    }
  }
  else
  {
     // switch is inactive
    if (BRIGHTNESS_UP > 0.12)
    {
      BRIGHTNESS_UP = BRIGHTNESS_UP / 1.2 ;
      kaimana.setLED(LED_UP, LED_UP_COLOR_ON, BRIGHTNESS_UP);
    }
    else
    {
      kaimana.setLED(LED_UP, BLACK, 1);
    }

    iLED[LED_UP] = false;
  }

    if(!digitalRead(PIN_DOWN))
  {
    switchActivity |= ATTACK_DOWN;
    // switch is active
    if(iLED[LED_DOWN] == true)
    {
      //maintain color while switch is active
      iLED[LED_DOWN] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_DOWN_ON      
        setLEDRandomColor(LED_DOWN);  
      #else
         kaimana.setLED(LED_DOWN, LED_DOWN_COLOR_ON, 1);
         BRIGHTNESS_DOWN = 1;
      #endif
      iLED[LED_DOWN] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_DOWN > 0.12)
    {
      BRIGHTNESS_DOWN = BRIGHTNESS_DOWN / 1.2 ;
      kaimana.setLED(LED_DOWN, LED_DOWN_COLOR_ON, BRIGHTNESS_DOWN);
    }
   
    else
    {
      kaimana.setLED(LED_DOWN, BLACK, 1);
    }

    iLED[LED_DOWN] = false;
  }



  // clear results for switch activity
  switchActivity = ATTACK_NONE;
  
  // test switch and set LED based on result       // HOME = GUIDE
  if(!digitalRead(PIN_HOME))
  {
    // switch is active
    if(iLED[LED_HOME] == true)
    {
      //maintain color while switch is active
      iLED[LED_HOME] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_HOME_ON      
        setLEDRandomColor(LED_HOME);  
      #else
         kaimana.setLED(LED_HOME, LED_HOME_COLOR_ON, 1);
      #endif
      iLED[LED_HOME] = true;
    }
  }
  else
  {
      // switch is inactive
      #ifdef RANDOM_COLOR_HOME_OFF
        setLEDRandomColor(LED_HOME);
      #else
        kaimana.setLED(LED_HOME, LED_HOME_COLOR_OFF, 1);
      #endif    
      iLED[LED_HOME] = false;
  }


  // test switch and set LED based on result    // SELECT = BACK 
  if(!digitalRead(PIN_SELECT))
  {
    // switch is active
    if(iLED[LED_SELECT] == true)
    {
      //maintain color while switch is active
      iLED[LED_SELECT] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_SELECT_ON        //mwolak 11-01-2015 switch between random or solid colors
        setLEDRandomColor(LED_SELECT);  //mappings in kaimana_custom.h
      #else
         kaimana.setLED(LED_SELECT, LED_SELECT_COLOR_ON, 1);
      #endif
      iLED[LED_SELECT] = true;
    }
  }
  else
  {
      // switch is inactive
      #ifdef RANDOM_COLOR_SELECT_OFF
        setLEDRandomColor(LED_SELECT);
      #else
        kaimana.setLED(LED_SELECT, LED_SELECT_COLOR_OFF, 1);
      #endif       
      iLED[LED_SELECT] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_START))
  {
    // switch is active
    if(iLED[LED_START] == true)
    {
      //maintain color while switch is active
      iLED[LED_START] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_START_ON        //mwolak 11-01-2015 switch between random or solid colors
        setLEDRandomColor(LED_START);  //mappings in kaimana_custom.h
      #else
         kaimana.setLED(LED_START, LED_START_COLOR_ON, 1);
      #endif
      iLED[LED_START] = true;
    }
  }
  else
  {
      // switch is inactive
      // switch is inactive
      #ifdef RANDOM_COLOR_START_OFF
        setLEDRandomColor(LED_START);
      #else
        kaimana.setLED(LED_START, LED_START_COLOR_OFF, 1);
      #endif      
      iLED[LED_START] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    
    // switch is active
    if(iLED[LED_P1] == true)
    {
      //maintain color while switch is active
      iLED[LED_P1] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_P1_ON
        setLEDRandomColor(LED_P1);
      #else
         kaimana.setLED(LED_P1, LED_P1_COLOR_ON, 1);
         BRIGHTNESS_P1 = 1;
      #endif
      iLED[LED_P1] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_P1 > 0.12)
    {
      BRIGHTNESS_P1 = BRIGHTNESS_P1 / 1.2 ;
      kaimana.setLED(LED_P1, LED_P1_COLOR_ON, BRIGHTNESS_P1);
    }
    else
    {
      kaimana.setLED(LED_P1, BLACK, 1);
    }
   
      iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_P2_ON
        setLEDRandomColor(LED_P2);
      #else
         kaimana.setLED(LED_P2, LED_P2_COLOR_ON, 1);
         BRIGHTNESS_P2 =1;
      #endif
      iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_P2 > 0.12)
    {
      BRIGHTNESS_P2 = BRIGHTNESS_P2 / 1.2 ;
      kaimana.setLED(LED_P2, LED_P2_COLOR_ON, BRIGHTNESS_P2);
    }
    else
    {
      kaimana.setLED(LED_P2, BLACK, 1);
    }
    
    iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_P3_ON
        setLEDRandomColor(LED_P3);
      #else
         kaimana.setLED(LED_P3, LED_P3_COLOR_ON, 1);
         BRIGHTNESS_P3 = 1;
      #endif
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_P3 > 0.12)
    {
      BRIGHTNESS_P3 = BRIGHTNESS_P3 / 1.2 ;
      kaimana.setLED(LED_P3, LED_P3_COLOR_ON, BRIGHTNESS_P3);
    }
    else
    {
      kaimana.setLED(LED_P3, BLACK, 1);
    }
    
    
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_P4_ON
        setLEDRandomColor(LED_P4);
      #else
         kaimana.setLED(LED_P4, LED_P4_COLOR_ON, 1);
         BRIGHTNESS_P4 = 1;
      #endif
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_P4 > 0.12)
    {
      BRIGHTNESS_P4 = BRIGHTNESS_P4 / 1.2 ;
      kaimana.setLED(LED_P4, LED_P4_COLOR_ON, BRIGHTNESS_P4);
    }
    else
    {
      kaimana.setLED(LED_P4, BLACK, 1);
    }    
    
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_K1_ON
        setLEDRandomColor(LED_K1);
      #else
         kaimana.setLED(LED_K1, LED_K1_COLOR_ON, 1);
         BRIGHTNESS_K1 = 1;
      #endif
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_K1 > 0.12)
    {
      BRIGHTNESS_K1 = BRIGHTNESS_K1 / 1.2 ;
      kaimana.setLED(LED_K1, LED_K1_COLOR_ON, BRIGHTNESS_K1);
    }
    else
    {
      kaimana.setLED(LED_K1, BLACK, 1);
    }    
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_K2_ON
        setLEDRandomColor(LED_K2);
      #else
         kaimana.setLED(LED_K2, LED_K2_COLOR_ON, 1);
         BRIGHTNESS_K2 = 1;
      #endif
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_K2 > 0.12)
    {
      BRIGHTNESS_K2 = BRIGHTNESS_K2 / 1.2 ;
      kaimana.setLED(LED_K2, LED_K2_COLOR_ON, BRIGHTNESS_K2);
    }
    else
    {
      kaimana.setLED(LED_K2, BLACK, 1);
    }    

    iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_K3_ON
        setLEDRandomColor(LED_K3);
      #else
         kaimana.setLED(LED_K3, LED_K3_COLOR_ON, 1);
         BRIGHTNESS_K3 = 1;
      #endif
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
    if (BRIGHTNESS_K3 > 0.12)
    {
      BRIGHTNESS_K3 = BRIGHTNESS_K3 / 1.2 ;
      kaimana.setLED(LED_K3, LED_K3_COLOR_ON, BRIGHTNESS_K3);
    }
    else
    {
      kaimana.setLED(LED_K3, BLACK, 1);
    }   
    iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      #ifdef RANDOM_COLOR_K4_ON
        setLEDRandomColor(LED_K4);
      #else
         kaimana.setLED(LED_K4, LED_K4_COLOR_ON, 1);
         BRIGHTNESS_K4 = 1;
      #endif
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive    
    if (BRIGHTNESS_K4 > 0.12)
    {
      BRIGHTNESS_K4 = BRIGHTNESS_K4 / 1.2 ;
      kaimana.setLED(LED_K4, LED_K4_COLOR_ON, BRIGHTNESS_K4);
    }
    else    
    {
      kaimana.setLED(LED_K4, BLACK, 1);
    }   

      iLED[LED_K4] = false;
  }



  // convert joystick, P1-P4, K1-K4 into a single unsigned int
  switchActivity = joystickDirection + switchActivity;
  kaimana.switchHistorySet(switchActivity);
  

  // test for combinations from most complext to least complex
  // test for switches in reverse order (newest to oldest)


  // combo #6
  // test for: Ultra 2 (Metsu Shoryuken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, DOWN, DOWN+RIGHT, RIGHT, RIGHT+K3
  if( kaimana.switchHistoryTest( COMBO_PATTERN_6A ) )
      animation_combo_6();

  // combo #5
  // test for: Ultra 1 (Metsu Hadouken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P3
  if( kaimana.switchHistoryTest( COMBO_PATTERN_5A ) )
      animation_combo_5();

  // combo #4
  // test for: Super (Shinkuu Hadouken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P1
  if( kaimana.switchHistoryTest( COMBO_PATTERN_4A ) )
      animation_combo_4();

  // combo #3
  // test for: Tatsumaki Senpukyaku (Hurricane Kick)
  // combo is: DOWN, DOWN+LEFT, LEFT, LEFT+K1 or LEFT+K2
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3A ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3B ) )
      animation_combo_3();

  // combo #2
  // test for: Ryu Shoryuken (Dragon Punch)
  // combo is: RIGHT, <NONE>, DOWN, DOWN+RIGHT, DOWN+RIGHT+P1 or DOWN+RIGHT+P2
  if( kaimana.switchHistoryTest( COMBO_PATTERN_2A ) )
      animation_combo_2();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_2B ) )
      animation_combo_2();

  // combo #1
  // test for: Ryu Hadouken (Fireball) 
  // combo is: DOWN, DOWN+RIGHT, RIGHT, RIGHT+P1 or RIGHT+P2  
  if( kaimana.switchHistoryTest( COMBO_PATTERN_1A ) )
      animation_combo_1();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_1B ) )
      animation_combo_1();


  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  



 

