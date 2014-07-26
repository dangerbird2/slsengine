all:build
all:$(ENGINE_TGT)
all:tests

CC=clang

#packages linked via pkg-config
PKGS= glib-2.0 csfml-all sfml-all

CFLAGS=-g -Wall -fblocks -std=gnu99 $(shell pkg-config --cflags $(PKGS)) -I$(CURDIR)/src
LDLIBS=$(shell pkg-config --libs $(PKGS)) -lBlocksRuntime -lSDL2 -lSDL2_image -lSDL2_mixer

#the main target build
ENGINE_NAME=libsrproto.a
ENGINE_SRC=$(wildcard src/**/*.c src/*.c)
ENGINE_HDR=$(wildcard src/**/*.h src/*.h)
ENGINE_OBJ=$(patsubst %.c,%.o,$(ENGINE_SRC))
ENGINE_TGT=lib/$(ENGINE_NAME)

.PHONY:$(ENGINE_NAME)
$(ENGINE_NAME): build $(ENGINE_TGT)

$(ENGINE_TGT): $(ENGINE_OBJ)
	ar rcs $@ $^

#test build

TEST_NAME=srprototest
TEST_SRC=$(wildcard tests/**/*.c tests/*.c)
TEST_HDR=$(wildcard tests/**/*.h tests/*.h)
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))
TEST_TGT=bin/$(TEST_NAME)

$(TEST_TGT):$(TEST_OBJ) $(ENGINE_TGT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

.PHONY:tests testdbg testvalgrind
tests: $(TEST_TGT)
	gtester $(TEST_TGT)

testdbg:$(TEST_TGT)
	gdb $(TEST_TGT)

testvalgrind:$(TEST_TGT)
	valgrind $(TEST_TGT)

.PHONY: build
build:
	@mkdir -p lib
	@mkdir -p bin




.PHONY: clean
clean:
	rm -rf build bin $(ENGINE_OBJ)
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#clang formatter command

FORMAT_OPTIONS=-style=LLVM
.PHONY: format
format:
	clang-format-3.3 -i $(FORMAT_OPTIONS) $(ENGINE_SRC) $(ENGINE_HDR)
