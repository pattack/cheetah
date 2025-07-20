CAR ?= habilis
APP ?= starter
BUILD_DIR = build/$(CAR)-$(APP)

.PHONY: all configure build clean

all: configure build

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake --preset=$(CAR)-$(APP) ../..

build:
	cd $(BUILD_DIR) && cmake --build .

clean:
	rm -rf build
