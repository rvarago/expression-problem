BIN_NAME=Main.linux

.PHONY: all build run clean

all: build

build:
	@$(MAKE) BIN_NAME=$(BIN_NAME) $@ -C cpp
	@$(MAKE) BIN_NAME=$(BIN_NAME) $@ -C haskell
	@$(MAKE) BIN_NAME=$(BIN_NAME) $@ -C rust

run:
	@find -name $(BIN_NAME) -exec ./{} \;

clean:
	@find -name $(BIN_NAME) -exec rm {} \;