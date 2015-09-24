Using a cheap STM32 Nucleo to teach remote sensor monitoring.
-------------------------------------------------------------

One of the major struggles as a University professor is to create
compelling examples for introductory courses to computer science. You
either end up with sterile toys, or bigger but hardly reusable examples.

Part of my students are enrolled in the Energetic Engineering track, so
I thought that it would be great to show them an example of embedded
system in that application domain.

In this small post, I'll sum up how I've built an embedded system for
temperature monitoring that sends data to an online plotting service
[Plot.ly](https://plot.ly).

Hardware
========

For this tutorial, I'll use an an [ST Nucleo
L053R8](https://developer.mbed.org/platforms/ST-Nucleo-L053R8/) as a
main board and a
[X-NUCLEO-IKS01A1Motion](http://www.st.com/web/catalog/tools/FM116/SC1248/PF261191)
sensor shield for measuring room temperature. For the remote connection,
I am going to use the PC as a bridge, by using a small custom proxy to
forward data to the remote service. As a future step, this can be
substituted by a wifi shield, to make the system completely autonomous.

![ST's boards stacked
toghether](https://dl.dropboxusercontent.com/u/5867765/images/File%2012-09-15%2015%2021%2006.jpeg)

Both boards can be bought at [Mouser](http://www2.mouser.com) for
approximately 26 USD, so they are pretty cheap, even for a student. The
boards are also compatible with the Arduino eco-system so there is no
risk of vendor locking, in the case you want to take this experiment a
little bit further.

Interestingly, the mounted ARM Cortex M0 has only 64Kb of flash memory
for programs and 8Kb of data RAM. While not necessarily the most
resource constrained, this proved to be rather challenging for
exchanging structured data between the Cortex and the PC.

Software Requirements
=====================

The whole build system is based on [Platform
IO](http://platformio.org/#!/), a very interesting project that allows
to setup, build and execute embedded programs by downloading, on demand,
the appropriate toolchain for an ever growing set of boards.

PlatformIO is built on Python so it is suggested to create a virtual env
before the installation:

``` sh
virtualenv env
source ./env/bin/activate h
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

The architecture
================

The sensor shield is connected to the STM32 through a
synchronous serial interface (I2C). I am going to write a small
firmware that initializes the sensor board and sends data through the
serial interface to the PC.

Those impatient can checkout the source code used in this tutorial from
[GitHub](https://github.com/vzaccaria/stm32l053) - see the `example2`
directory.

Just `cd` into one of the `example*` directories; then, with the board
attached run `platform run`

Example 1
---------

Just a simple program to get T,H,P sensor values and print them on the
serial port.

commands:
---------

-   `make run` to compile and flash on the board
-   `make watch` to watch data sent over the wire

Example 2
=========

Plots realtime temperature on [plotly](https://plot.ly/). To enable
plotting:

1.  you should create a `tools/plotly-config.json` with your plotly
    credentials:

    ``` json
    {
        "user": "foo",
        "apikey": "bar",
        "token": "kookoo"
    }
    ```

2.  install the required modules with `npm install .`

commands
--------

-   `make run` to compile and flash on the board
-   `make plot` to plot data on plotly

![Remote monitoring](http://g.recordit.co/sMGqnFe5gZ.gif)
