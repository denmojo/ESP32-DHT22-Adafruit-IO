# ESP32-DHT22-Adafruit-IO
Doit ESP32 Espressif board with DHT22 temperature sensor

http://bit.ly/2LM2lix - ESP32 board

http://bit.ly/2Gy3hmo - DHT22 sensor

I wrote this code to monitor my ham radio shack (a.k.a. my garage) temperature over time.

It uses a cheap ESP32 Arduino board to talk via my wifi network, and uses pin D4 to grab data from the DHT22 temperature/humidity sensor. The code then uses Adafruit MQTT to post the data to Adafruit IO for dashboard of temperature trends.

https://io.adafruit.com

This was all compiled in Arduino IDE and flashed to the board over USB cable.

Make sure you have Adafruit MQTT and DHT sensor libraries installed in the IDE, as well as the requisite ESP32 libraries to access wifi.


## Connecting to the DOIT Dev Kit V1 board
To talk to this undocumented board, I used DOIT ESP32 DEVKIT V1 board

by adding Additional Boards Manager URL: https://dl.espressif.com/dl/package_esp32_index.json

and downloaded the USB to UART drivers for serial port access

https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

Additionally, I set the "Programmer" in Arduino to "USBtinyISP" and held down the "Boot" button on the board when uploading the code to the board.