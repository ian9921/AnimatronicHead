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
