# Plant-O-Matic
Arduino UNO based hydroponic project for a self-sufficient plant.

# ACTUAL SITUATION 
Actually Flashing this firmware on an arduino nano board connected to a pump and a ground sensor provides a self sufficient plant with a control display and also offers the possibility to connect a 5V led stripe that could be powered on a specific light-cycle.  

# WORKING ON
Implementing a circular menu button to manage irrigation settings. 

# ROADMAP
V0.1) Automatic Water signaling
  When water level into the ground goes down, led blinks. Measures every hour, hardware enabling circuit to preserve it. 
V1) Automatic water filling
  When ground sensor indicates a low humidity (2 measures in a day to preserve sensor) on terrain, pump starts. Activity Led, serial Logging.
V1.1) Empty Tank Failsafe
  Adding hardware-based failsafe circuit to disable water pump if water reaches a too low level. Activity Led starts to blink.
V1.2) Display
  Adding display to show plant status
V1.3) UV Lamp
V1.4) WIFI Serial Communication, web status check.
V1.5) Other Base Features TODO
V2) App control plant / Telegram Bot

# Materials (easy to find on ebay):

- Arduino UNO/Nano ATMEGA Microcontroller 
- MicroPump 5V
- Cables and breadboard
- Transistor (wip)
- 3x Leds (Red, green, yellow)
- empty tank sensor
- Ground sensor 
- OLED string Display
