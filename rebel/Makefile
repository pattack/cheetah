BOARD ?= stm32f103
BUILD_DIR = build/$(BOARD)

.PHONY: all configure build clean

all: configure build

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake --preset=$(BOARD) ../..

build:
	cd $(BUILD_DIR) && cmake --build .

clean:
	rm -rf build
