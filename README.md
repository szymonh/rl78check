# rl78check

rl78check is an Arduino-based Platformio project which checks flash security configuration of connected RL78 MCU.

## How does it work?

The app communicates with a RL78 chip over single wire serial interface using Protocol A. After initializing the connection _get silicon signature_ and _get security_ commands are executed to retrieve MCU data and settings. The information are further printed over primary serial.

## How to use it?

After updating TOOL0_PIN and RESET_PIN to match your configuration build and upload the project. Since a hardware serial in half-duplex mode is utilized to communicate with RL78 please make sure to match TOOL0_PIN with the UART TX pin. Connect TOOL0_PIN and RESET_PIN to corresponding RL78 pins and you are ready to go. Open up a serial console and press any key to trigger communication with the MCU. Acquired results will be printed over primary serial with baudrate of 115200.

## How does it look like?

```
Silicon signature
DEC: 10 00 06 
DEV: 52 35 46 31 30 32 36 41 20 20 
CEN: ff 3f 00 
DEN: ff 17 0f 
VER: 03 00 03 

MCU Security
FLG: fe 
BOT: 03 
SSL: 00 
SSH: 00 
SEL: 0f 
SEH: 00 

Security flag properties
        Programming enabled
        Block erase enabled
        Boot block cluster rewrite enabled
        Boot area exchange flag not provided

Press any key to continue ..
```

## Notes

- tested on BluePill with Renesas RL78 G13
