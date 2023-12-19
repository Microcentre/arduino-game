# 'Roids

## Hardware
- Arduino Uno
- Game Shield
- Adafruit ILI9341 display is installed.
- Wii Nunchuk

## Build Instructions
1. Clone the repository
2. Install [VSCode](https://code.visualstudio.com/)
3. Install the [PlatformIO extension](https://platformio.org/platformio-ide)
4. Open the repository in VSCode. PlatformIO should recognize it and begin installing dependencies.
5. Open `src/Hardware/Display.cpp`
6. On line 7, Ctrl + click on `begin()`
7. A new file will open. In this file, Ctrl + F for "delay" and replace all occurrences with "_delay_ms"
8. Build and upload the project
