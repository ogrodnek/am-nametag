![CI](https://github.com/ogrodnek/am-nametag/workflows/CI/badge.svg)

HELLO! My Name Is LED Nametag Kit
=================================

Your name in lights! Spell out up to 5 characters


Project description: [Analog Machines Nametag](http://analogmachines.com/p/nametag)


With the HELLO! My Name Is LED Nametag Kit you can stand out from the crowd, 
instead of scrawling your name on the ubiquitous "Hello, My Name Is:" stickers.
Next time you're at a meet and greet party at your local hackerspace, there 
will be no mistaking that you are a maker.

The nametag kit is a perfect first or second soldering project and is the 
greatest alternative to stick on name tags that we've ever seen.


It comes with 4 built-in programs: all on, letter chase, fade, and blink. 
There's also a power saving mode.

As part of the project, we've developed a simple [font and a name layout tool]
(http://analogmachines.com/p/nametag/name.html). 
Right now, our font only supports 5 letters or less. 
Check it out and see how your name will look! 



Check out the [build instructions](http://analogmachines.com/p/nametag/build/) 
for an idea of what's involved.

Compile instructions
--------------------

For Linux you need to have avr-gcc, avr-libc and binutils-avr installed. For 
Windows you need WinAVR.

After cloning this project you can compile it simply by entering:
`cd "path to your project location"`
`make`


If you also have avrdude installed you can also write the programm to the 
microcontroller (to "flash" it):
`make program`

If you have a different programmer than the default you can pass parameters
to avrdude. This example is for the Atmel Dragon using ISP:
`make program AVRDUDE_PORT=usb AVRDUDE_PROGRAMMER=dragon_isp`
