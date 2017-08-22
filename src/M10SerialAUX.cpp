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

//----------------------------------------------------------------------------
// serial_aux_begin()
//
// Parameters:
//      rate : baud rate, set it to 115200
//
// Return Value:
//      None
//
// Remarks:
//      function to init the serial port
//----------------------------------------------------------------------------

static uint32_t aux_serial_rate_factor = 833; // 96e6 / 115200 

static void serial_aux_begin (uint32_t rate) __reentrant
{
    uint32_t tmp;
    
    //================================
    // If CPU clock is 100MHz
    //================================
    // 100e6 / 115200 = 868
    // 65536 - 868 = 64668 = 0xFC9C
    //TL0 = 0x9C;
    //TH0 = 0xFC;
    
    //================================
    // If CPU clock is 96MHz
    //================================
    // 96e6 / 115200 = 833
    // 65536 - 833 = 64703 = 0xFCBF
    //TL0 = 0xBF;
    //TH0 = 0xFC;
        
    
    //TMOD = 0x10;
    //TR0 = 1;
    
    TR0 = 0;
    
    ET0 = 0;
    EA = 0;
    
    __asm__ ("nop");
    __asm__ ("nop");
    __asm__ ("nop");
    __asm__ ("nop");
    
    aux_serial_rate_factor = 96000000 / rate; 
    tmp = aux_serial_rate_factor;
    tmp = 65536 - tmp;
    
    TL0 = (uint8_t)(tmp & 0xFF);
    TH0 = (uint8_t)((tmp >> 8) & 0xFF); 

     
    TMOD = 0x11;
    TR0 = 1;
    
    SCON_AUX = 0xC0;
    __asm__ ("nop");
    __asm__ ("nop");
    
    ET0 = 1;
    EA = 1;
    
} // End of serial_aux_begin()


//----------------------------------------------------------------------------
// serial_aux_putchar()
//
// Parameters:
//      c    : byte to write to the serial port
//
// Return Value:
//      None
//
// Remarks:
//      function to send a byte to the serial port
//----------------------------------------------------------------------------

static void serial_aux_putchar (uint8_t c) __reentrant
{
    SCON_AUX &= 0xEF; // REN = 0;
 
    SBUF_AUX = c;
    while (!(SCON_AUX & 0x02));

    SCON_AUX &= 0xFD; //  TI = 0;              
} // serial_aux_putchar()

//----------------------------------------------------------------------------
// serial_aux_available()
//
// Parameters:
//      None
//
// Return Value:
//      1 if the serial port's receiving buffer is not empty
//      0 if the receiving buffer is empty
//
// Remarks:
//      function to check if the serial port's receiving buffer is empty 
//      or not
//----------------------------------------------------------------------------

static uint8_t serial_aux_available() __reentrant
{

    if (!(SCON_AUX & 0x10)) { // REN == 0;
        SCON_AUX |= 0x10;  // REN = 1
    }

    if (SCON_AUX & 0x01) { // RI
        return 1;
    } else {
        return 0;
    }
        
} // End of serial_aux_available()


//----------------------------------------------------------------------------
// serial_aux_write()
//
// Parameters:
//      buf        : pointer to the data buffer
//      length     : the number of bytes vaild in the buffer
//
// Return Value:
//      None
//
// Remarks:
//      function to write data buffer to the serial port
//----------------------------------------------------------------------------

static void serial_aux_write (uint8_t* buf, uint16_t length) __reentrant
{
    if (length) {
        while (length) {
            serial_aux_putchar ((*buf++));
            --length;
        } // End of while loop
    } else {
        while (*buf) {
            serial_aux_putchar ((*buf++));
        } // End of while loop
    }
    
} // End of serial_aux_write()


//----------------------------------------------------------------------------
// serial_aux_receive()
//
// Parameters:
//      None
//
// Return Value:
//      byte received from the serial port
//
// Remarks:
//      function to receive a byte from the serial port, unblocked fashion
//----------------------------------------------------------------------------
static uint8_t serial_aux_receive () __reentrant
{   
    uint8_t k;

    SCON_AUX |= 0x10;  // REN = 1
    
    k = SBUF_AUX;
    SCON_AUX &= 0xFE; // RI = 0; 
    return (k);
    
} // End of serial_aux_receive()



const SERIAL_AUX_STRUCT SerialAUX = {
  .begin = serial_aux_begin,
  .available = serial_aux_available,
  .read = serial_aux_receive,
  ._write = serial_aux_write
};
