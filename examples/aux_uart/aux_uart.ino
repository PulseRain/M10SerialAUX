/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#include "M10SerialAUX.h"

//============================================================================
// Example:
//    Auxiliary Serial Port demonstration. To use this example, you need to 
// connect the AUX serial port (pin 1 - RX, pin 1 - TX, on Arduino UNO Rev 3) 
// to a PC through a FT232RL (such as the SparkFun USB to Serial Breakout - 
// FT232RL).
//
// On Windows, connect a Tera Term to the AUX serial port. And connect
// Arduino to the board through the main serial port. Open the Serial
// Monitor. Set the Tera Term to be 921600 bps, and set the Serial Monitor
// to be 115200 bps.
//
// Type something in the Tera Term Windows, and the same characters will
// show up in the Serial Monitor. 
//============================================================================


//============================================================================
// setup()
//============================================================================

void setup() {
  SerialAUX.begin(921600);
  Serial.begin (115200);
  delay (1000);
} // End of setup()



//============================================================================
// loop()
//============================================================================

void loop() {
  uint8_t t;
  
  if (SerialAUX.available()) {
    t =  SerialAUX.read();  
    Serial.write (&t);
  }
} // End of loop()
