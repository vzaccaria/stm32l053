Installation
============

``` sh
virtualenv env
source ./env/bin/activate # zsh
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

Issues that may arise[^1][^2]

[^1]: For the `--egg` option see:
    [link](https://github.com/platformio/platformio/issues/279)

[^2]: `pip` caches are owned by root and need to be chmodded.

# Use
Just `cd` into one of the `example*` directories; then, with the board attached run `platform run`
