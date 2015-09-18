![ST's boards stacked
toghether](https://dl.dropboxusercontent.com/u/5867765/images/File%2012-09-15%2015%2021%2006.jpeg)

This very simple project shows how to use an [ST Nucleo
L053R8](https://developer.mbed.org/platforms/ST-Nucleo-L053R8/) with a
[X-NUCLEO-IKS01A1Motion](http://www.st.com/web/catalog/tools/FM116/SC1248/PF261191)
MEMS and environmental sensor expansion board.

It is based on the demo and code found on the [ARM mbed
website](https://developer.mbed.org/teams/ST-Americas-mbed-Team/code/Nucleo_Sensor_Shield/).

The whole build system is based on [Platform
IO](http://platformio.org/#!/).

Installation
============

``` sh
virtualenv env
source ./env/bin/activate # zsh
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

Use
===

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

Plots realtime temperature on [plotly](https://plot.ly/). To enable plotting:

1. you should create a `tools/plotly-config.json` with your plotly credentials:

    ``` json
    {
        "user": "foo",
        "apikey": "bar",
        "token": "kookoo"
    }
    ```
2. install the required modules with `npm install .`

commands
--------

-   `make run` to compile and flash on the board
-   `make plot` to plot data on plotly
