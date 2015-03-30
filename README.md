#RFID Based Security System

Software required:
AVR Studio 4.18
Sinaprog
Winavr
Realterm or Putty(For Monitoring the system on Computer)
Proteous (if u need to simulate it virtually)
For burning the chip:
AVR development board .
ISP Programmer 
Hardware or Components required
Rfid Module with 4 tags
AVR controller(ATmega16)
16x2 Alphanumeric LCD
Max232 (TTL converter)
Diode(1N4001/1N4007)
Resister(390 ohm)
Preset/POT(50k)
Capacitor(1000uf,10uf)
Led(red or green)
LM7805/7812(both are required)
Motor (150 RPM)
L293D(Motor Driver)
Transformer (12-0-12)(1 amp)
Use a CD Tray to test the Dummy project(without using the L293d and a Motor).
Circuit Connection:
Connect  the circuit as connected in the Diagram given.
Then give the power supply to the circuit. Then swap the card on RFID tag .
Fast test the Card on Swiping with RFID check what number is coming  in LCD or in Desktop. According to that set the array bits to functional it properly. 
Use a usb to serial converter (Prolific).for that a  Usb to serial driver is requred to install on Desktop.


