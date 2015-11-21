.PHONY: clean upload

SOURCES := $(wildcard src/*) $(wildcard lib/ESP8266AVRISP/*)


.pioenvs/esp01/firmware.bin: $(SOURCES)
	platformio run

clean:
	platformio run --target clean

upload: .pioenvs/esp01/firmware.bin
	../vendor/esptool.py --port /dev/cu.usbserial --baud 115200 write_flash 0x00000 .pioenvs/esp01/firmware.bin
