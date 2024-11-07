compile: holonomic.ino motor.ino network.ino motor.h network.h definitions.h
	arduino-cli compile -b esp32:esp32:esp32doit-devkit-v1 ./

upload: compile
	arduino-cli upload -b esp32:esp32:esp32doit-devkit-v1 -v -p /dev/ttyUSB1 ./
