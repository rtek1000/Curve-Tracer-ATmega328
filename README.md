# Curve Tracer ATmega328
Fault locator for electronic circuits, comparing V.I. curves (voltage and current)

Open source firmware based on "InvCurv"

This software is based on the operation of "InvCurv" marketed by "www.InverFlex.com.br".

Attention: This repository has no connection with this company, in any way, no complaints about the functioning of the device should be registered in this repository.

- Todo: Check DIDR register in setup.
- - Ref.: http://www.openmusiclabs.com/learning/digital/atmega-adc/index.html

- Todo: Remove the use of the TimerOne library, because it is not GPL compliant.
- - Ref.: https://www.diffen.com/difference/Creative_Commons_License_vs_GPL

--------------

---> To use this device, it is necessary to use the computer software (Microsoft Windows executable) supplied by the manufacturer, shipped with the device and cables.
This device is just an interface between the printed circuit board to be tested and the computer that compares the V.I. curves.

If you want to know another project of this type of device, go to this link:
https://hackaday.io/project/16704-microcontroller-based-curve-tracer

The website of another company that manufactures this type of defect locator can be accessed at this link:
https://www.abielectronics.co.uk/

--------------

This software is for educational purposes only and should not be considered a reliable replacement for the original product software.

---> Do not replace the original firmware of the product, otherwise you may lose the warranty offered by the manufacturer.

The original device is produced with a microcontroller and its software is locked for reading, it is not possible to save the original firmware, for backup, for repair, in case the microcontroller fails.

Also, the hardware is sold with sanded components, the original codes cannot be read. Therefore, the suggested codes may not be the same as the originals.

The shield board is originally soldered directly to the Arduino board, no pin female header is used.

Note: Program code has been tested only on ATmega328P (Arduino UNO, Pro Mini etc) should not work with Arduino Mega 2560 and others

Original board: https://store.arduino.cc/usa/arduino-uno-rev3

If you are curious to know what is inside the device box, as the device is sold with a security seal: Do not remove the security seal, as this may void the manufacturer's warranty.

Note: Unless required by applicable law or agreed to in writing, the contents of this repository may only be used in an educational manner "AS IS", WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, express or implied.

--------------

(The oscilloscope images are from a DSO150, if you want to find open source software for it, check this repository: https://github.com/Jason2866/Open-DSO-150 )

--------------

Library used in this software: https://www.arduino.cc/reference/en/libraries/timerone/

--------------

Software License:
This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
