This very simple project shows how to use an [ST Nucleo
L053R8](https://developer.mbed.org/platforms/ST-Nucleo-L053R8/) with a
[X-NUCLEO-IKS01A1Motion](http://www.st.com/web/catalog/tools/FM116/SC1248/PF261191)
MEMS and environmental sensor expansion board.

It is based on demo and code found on the [ARM mbed website](https://developer.mbed.org/teams/ST-Americas-mbed-Team/code/Nucleo_Sensor_Shield/).

Installation
============

``` sh
virtualenv env
source ./env/bin/activate # zsh
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

Issues that may arise[^1][^2]

Use
===

Just `cd` into one of the `example*` directories; then, with the board
attached run `platform run`

[^1]: For the `--egg` option see:
    [link](https://github.com/platformio/platformio/issues/279)

[^2]: `pip` caches are owned by root and need to be chmodded.
