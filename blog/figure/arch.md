```
K.K

SL.   Pl.   Y..
.F    .y.   ...
..S   ..P   ..Y
```







| node  | label       | type      |
| ----- | -----       | ---       |
| L     | STM32L053   |           |
| S     |             | rectangle |
| P     |             | rectangle |
| l     | PC          |           |
| Y     | Plot.ly     | rectangle |
| K     | Sensor      | rectangle |
| F     | Firmware    | rectangle |
| y     | stm32-proxy | rectangle |


| src  | dst  | style  | curve | label                    | through  | pattern |
| ---- | ---- | -----  | ----- | -----                    | -------- | ------- |
| F    | y    | =>     |       | \small serial (protobuf) |          |         |
| y    | Y    | ->     |       | \small Internet          |          |         |
| K    | S    | -latex |       | \small I2C               |          |         |
