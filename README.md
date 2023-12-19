# 'Roids

## Hardware Requirements
- Arduino Uno
- Game Shield provided by Windesheim University of Applied Sciences
- Adafruit ILI9341 display
- White ZX-Nunchuk

## Build Instructions
1. Clone the repository
2. Install [VSCode](https://code.visualstudio.com/)
3. Install the [PlatformIO extension](https://platformio.org/platformio-ide)
4. Open the repository in VSCode. PlatformIO should recognize it and begin installing dependencies.
5. Open `src/Hardware/Display.cpp`.On line 7, Ctrl + click on `begin()`
    - (Alternatively, find and open `.pio\libdeps\uno\Adafruit ILI9341\Adafruit_ILI9341.cpp` directly).
7. A new file will open. In this file, Ctrl + F for "delay" and replace all occurrences with "_delay_ms"
8. Build and upload the project
