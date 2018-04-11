# Disclaimer and warning

The instructions, images, schematics, source codes, etc. may not be accurate nor complete.
Use at your own risk.

LEGO® is a trademark of the LEGO Group of companies which does not sponsor, authorize or endorse this site.

**Attention**: Please note that there are two projects with the name "Leguino" out there:

1. This open-source, free GitHub project, focussing on the creation of an Arduino shield to drive standard LEGO® Technic motors and lights. You can find more details on the history of the project in this readme, and at [Thomas Jacob's website](https://www.thomasjacob.de/kreativ/leguino-en). In this project, you take your existing LEGO® Technic models and bring them to life by programming against an Arduino API.

2. A commercial project, started as a Kickstarter campaign, focussing on the creation of proprietary hardware bricks compatible to the geometry of LEGO®, with Arduino and Raspberry Pi programming. You can find more details on that project at [Leguino.com](http://leguino.com).

# Introduction

[LEGO<sup>®</sup> Mindstorms](https://www.lego.com/de-de/mindstorms) is a wonderful platform to playfully get used to robotics and programming. Kids can complete their existing LEGO<sup>®</sup> collection with motors and sensors, and the graphical programming environment is easy to understand, but it also contains complex concepts like commands, iterations, branching, variables, and events.

LEGO<sup>®</sup> Mindstorms is, on the other hand, not very cheap (especially for the inquisitive offspring). Though my son already had a rich collection of LEGO<sup>®</sup> Technic models with motors, lights, and switches, it lacks of sensors and even programming.

But he was very much interested in that stuff.

So I thought, let's try to fill the gap and build an open-source platform based on LEGO<sup>®</sup> Technic, that is cheap enough (goal <100€) and also easy to understand. To do so, [Arduino](https://www.arduino.cc/) is the perfect choice, for the following reasons:

* An Arduino Nano costs less than 20€, sometimes even below 10€.
* You can power it with a regular LEGO<sup>®</sup> Technic battery.
* It starts up in less than a second (in contrast to the [Raspberry Pi](https://www.raspberrypi.org/) for instance), a circumstance that is important when building models with a switchable battery.
* It has enough inputs/outputs for about 10 devices.

I added a programming platform, an API that abstracts from sensors, actors, control sequences etc., so the offspring (and you) can focus on the actual project.

If you want to learn more about how Leguino was invented, [visit my web site](http://www.thomasjacob.de/kreativ/leguino-en).

# Getting started

Leguino is both a custom Arduino shield and wiring, as well as a library for Arduino. To get started, you need to build the shield yourself (sorry, no orderable ready-made PCB as of today), and then install the Arduino IDE, and the Leguino library.

## Hardware

First of all, you require an Arduino Uno or Nano. I recommend the latter, as it fulfills the Leguino requirements and it has much smaller dimensions.

As there is no Leguino PCB design as of today (maybe you'd like to contribute?), you need to buy an Arduino shield and all electronics parts, and solder them manually.

You also need to make LEGO<sup>®</sup> Technic wires and the case.

You can find all parts in the [parts list](docs/parts.md), as well as wiring and board schematics in [schematics folder](docs/schematics). I also took [some pictures](docs/photos) while building the prototype. Maybe my [my web site](http://www.thomasjacob.de/kreativ/leguino-en) helps, too.

## Software

To write your own Leguino program, you first need the Arduino IDE, which you can [download here].

After installation, take this Leguino source folder, and put it into the libraries folder of your installation.

Then, start your programs by using one of the example sketches found in [examples)(examples), and read the API of the [Leguino core](core/LeguinoCore.h), [its actors](actor/Actor.h), and [its sensors](sensor/Sensor.h).

There is also a kids-friendly (but German) documentation available, [see here](docs/Leguino-Kurzanleitung-DE.doc).

# Contribute

Do you have suggestions, ideas, even code or PCB designs? Please contact me at http://thomasjacob.de/footer/contact.
