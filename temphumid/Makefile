.PHONY: clean upload


.pioenvs/esp01/firmware.bin: src/tempserver.ino src/tempserver.h
	platformio run

clean:
	platformio run --target clean

upload:
	platformio run -t upload
