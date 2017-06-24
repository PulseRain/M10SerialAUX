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

#ifndef M10SERIALAUX_H
#define M10SERIALAUX_H

#include "Arduino.h"


typedef struct {
   void (*begin) (uint32_t); 
   uint8_t (*available)();
   uint8_t   (*read)();
   void (*_write) (uint8_t* buf, uint16_t length) __reentrant;
} SERIAL_AUX_STRUCT;

extern const SERIAL_AUX_STRUCT SerialAUX;


#endif
