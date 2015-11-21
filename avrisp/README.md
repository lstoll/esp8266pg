# avrisp

Use the ESP8266 as a flasher for arduinos. Use for flashing optiboot on cheap nano clones

    avrdude -c arduino -p ATmega328P -P net:172.16.51.136:328 -U flash:w:"/opt/homebrew-cask/Caskroom/arduino/1.6.5-r5/Arduino.app/Contents/Java/hardware/arduino/avr/bootloaders/optiboot/optiboot_atmega328.hex"

Used a 10k pull up resistor on the reset pin.

Once flashed, treat it as a uno
