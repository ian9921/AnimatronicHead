# AnimatronicHead
Code and documentation for my hand-held animatronic head

This is a simple project I started as a fun halloween project. It is a simple hand-held animatronic that can double as a manually-operated handpuppet.
The puppet has been constructed and some basic lights have been added, powered by an ArduinoUno. The next step is to write the code to properly implement other animatronic elements aswell.


# How To Use It
The animatronic/puppet "skull" was constructed generally by following this tutorial: https://www.instructables.com/DIY-Muppet-Puppet/
Current electrical components are a simple ArduinoUno, an Adafruit Neopixel 20-LED strip, and a standard 2-port USB power bank

# Implementing the Lights
First step is powering the lights. The Arduino's 5V pin does not provide enough current, so I elected to use the power bank instead. Take the two power pins for the Neopixel strip and connect them to a male USB. Adapters to achieve this are easily available, I picked one up from Adafruit.

Now, connect the data pin of the Neopixels to pin 12 on your Arduino.

If everything is done properly, you can now build & upload MainBrain to your board, and when both the board and lights are plugged into your battery pack many of the LEDS will flicker orange and the two associated with the eyes will be a constant red that occaisonally "blinks" off  for a half second.

It's important to note that you should make sure you use the same battery pack for both the board and the lights, since most power banks have an unadvertised feature where if they don't detect enough current draw, they stop providing power all together. Neither the board nor the lights individually draw enough current to get around this, but together they do.

# Implementing The Keypad Controls
For this, I used a simple 4x4 keypad like the one found here: https://www.amazon.com/outstanding-Adhesive-Membrane-Keyboard-Prototyping/dp/B08JYNM8D9?source=ps-sl-shoppingads-lpcontext&ref_=fplfs&psc=1&smid=AB0Z3CZXYVM06&gQT=1
[SEL Values Brochure-1.pdf](https://github.com/user-attachments/files/18374251/SEL.Values.Brochure-1.pdf)
![headKeypad](https://github.com/user-attachments/assets/61b6d8b2-2299-45bd-acf1-f2cb2861e6fa)
![5-00 Exploring the Wastes Player Version](https://github.com/user-attachments/assets/9ba18477-539f-4018-b62b-de2764ffc366)
![5-00 Exploring the Wastes](https://github.com/user-attachments/assets/4c0ad2b3-ff06-4edb-b06e-66797e0a1f9c)
![5-00 Exploring the Wastes(1)](https://github.com/user-attachments/assets/a286707a-6e76-41ab-804a-4395cc8dc729)

Looking down on the keypad as in the picture, connect each pin from left to right to the arduino pins 9, 8, 7, 6, 5, 4, 3, and 2. If done properly, when you upload the sketch you can now manually control when the eye lights "blink". Pressing the "*" button will cause the head to toggle between automatic and manual blink mode. In automatic, the head blinks on its own. In manual, pressing the "7" key will toggle the states of the eye lights.

The keypad is flimsy, so be sure to secure it. You can secure it anywhere that is convenient for your control use case.

# Implementing the Eyelid Servos
For the eyelid servos, this project uses simple SG90 servos like those available here: https://www.amazon.com/Micro-Helicopter-Airplane-Remote-Control/dp/B072V529YD?source=ps-sl-shoppingads-lpcontext&ref_=fplfs&psc=1&smid=A34CQKEVNF2MJX&gQT=2

Connect the red pin to your arduino's 5v pin, the black pin to ground, and the yellow pin to arduino pin 12. If done properly, whenever the head "blinks", the servo will rotate 90 degrees. When the lights turn off it turns clockwise, and when the lights turn on it turns counterclockwise.
