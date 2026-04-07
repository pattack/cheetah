CAR ?= habilis
APP ?= starter
BUILD_DIR = build/$(CAR)-$(APP)

.PHONY: all configure build clean

all: configure build

configure:
	cmake --preset=$(CAR)-$(APP)

build:
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
