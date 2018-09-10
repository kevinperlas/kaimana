###### Hi! 
If you are here then you probably saw my lighting effect on [Reddit](https://www.reddit.com/r/fightsticks/comments/9dpi9a/reactive_lighting_effect/). Unfortunately, my Mini is no longer accepting new code or able to roll back to stable code. Manual reset doesn’t seem to be working either so development to generalize my code has stopped until I fix it or buy a new one :sadface: . I’ve had so many hardware issues with the Kaimana Mini and the J2s that I need a break before I sink even more time/money into this exercise of frustration. Anyways, I uploaded the code in its current state if you or anyone wants expand upon what I’ve made.

So here are the changes from the brightstick arcade download. 

On the main INO file, there is a global variable (type float) for every button (*eg BRIGHTNESS_P1*). This will be a value between 1-0.

The SetLED method in the Kaimana class now takes a 5th input variable of type float. [EVERYTHING that calls this method has to be updated to accommodate this change]. The brightness variable that multiplies the RGB values by a ratio.

**The fading effect isn’t an animation. It takes place in the “Switch Activity” in the main INO file.**

When a button is “active” (*ie pressed down*). Example for P1:

* It passes to `SetLED(LED_P1, [RGB values for P1], 1) `
* `BRIGHTNESS_P1 = 1` (Resets the corresponding BRIGHTNESS variable to 1)

When a button is “inactive” (*ie not pressed*). Example for P1:
*	If/Else operation to see if the corresponding BRIGHTNESS value is below a threshold. (Currently 0.12)
  *	True: set the color to black. (BLACK is predefined as 0,0,0)
*	SetLED(LED_P1, BLACK, 1)
  *	False: reduce the brightness then pass the value to the SetLED method. 
`BRIGHTNESS_P1 = BRIGHTNESS_P1 / 1.2`
`SETLED(LED_P1, [RGB values for P1], BRIGHTNESS_P1)`

The board updates the LEDs every ~50ms (x20/sec) 

**Some notes:** I chose `BRIGHTNESS_P1 = BRIGHTNESS_P1 / 1.2` is a simple recursive decaying formula based on how often the switch activity updates the LED colors (in this code it would update x10 over 600ms before going black). I was experimenting with the minimum threshold and the timings before my mini decided to die. Another formula I wanted to try was `BRIGHTNESS_P1 = exp(1.5 * BRIGHTNESS_P1)` which is the exponential decay formula where the 1.5 is just a constant that you can change to alter the rate of decay. 

The previous formulas had the brightness decay rapidly but then “flatten out” and linger at lower brightness. Another Idea was to “flip the curve.” Linger at a higher brightness then rapidly accelerate to zero over time. This is closer to what the Razer keyboards do. I don’t think it would look good on an arcade stick since keyboards have way more buttons instead of just mashing on the same 6 buttons. It might look good, worth an experiment. 

You could also do a linear decay but where’s the fun in that? Plus, I hear that a non-linear fade is more pleasing to the human eye. 





---







Paradise Arcade Shop Kaimana LED Driver Board
Initial Release October 15, 2013

Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com  
All rights reserved.  Use is subject to license terms.

Code is provided for entertainment purposes and use with the Kaimana controller.
Code may be copied, modified, resused with this Copyright notice.
No commercial use without written permission from Paradise Arcade Shop.

Paradise Arcade Shop Kaimana LED Driver Board
Initial Release October 15, 2013

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.



The Kaimana class library is based on original source released by ParadiseArcadeShop.com
with feedback from the community.
