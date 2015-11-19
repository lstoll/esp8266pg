.PHONY: clean upload


.pioenvs/esp01/firmware.bin: src/flash.ino
	platformio run

clean:
	rm -rf .pioenvs

upload: .pioenvs/esp01/firmware.bin
	../vendor/esptool.py --port /dev/cu.usbserial --baud 115200 write_flash 0x00000 .pioenvs/esp01/firmware.bin
