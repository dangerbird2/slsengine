all:build
all:$(ENGINE_TGT)
all:demo

CC=clang

#packages linked via pkg-config
PKGS= glib-2.0

DEPS= \
	GL 			\
	GLEW 		\
	SDL2 		\
	SDL2_image 	\
	SDL2_mixer 	\
	3ds			\
	BlocksRuntime \
	dispatch		\
	CoreFoundation


#clang analyzer conventions
CHECK_CONVENTIONS=	\
	-analyze 	\
	-Xanalyze -analyzer-check-llvm-conventions	\
	-Xanalyze  -analyzer-check-dead-stores		\

CFLAGS= \
	-g 	\
	-Wall \
	-std=gnu11 \
	-O0			\
	-fblocks 	\
	$(shell pkg-config --cflags $(PKGS)) \
	-I$(CURDIR)/src/ \
	-D __SLS_QUIET__ \
	-D __GNU_SOURCE
LDLIBS=-lm 	\
	-pthread	\
	$(patsubst %, -l%, $(DEPS))	\
	$(shell pkg-config --libs $(PKGS))


#the main target build
ENGINE_NAME=libsls.a
ENGINE_SRC=$(wildcard src/slsengine/**/*.c src/slsengine/*.c)
ENGINE_HDR=$(wildcard src/slsengine/**/*.h src/slsengine/*.h)
ENGINE_OBJ=$(patsubst %.c,%.o,$(ENGINE_SRC))
ENGINE_TGT=lib/$(ENGINE_NAME)

.PHONY:$(ENGINE_NAME)
$(ENGINE_NAME): build $(ENGINE_TGT)

$(ENGINE_TGT): $(ENGINE_OBJ)
	ar rcs $@ $^

DEMO_NAME=demo
DEMO_SRC=$(wildcard src/demo/*.c wildcard src/demo/**/*.c)
DEMO_OBJ=$(patsubst %.c, %.o, $(DEMO_SRC))
DEMO_TGT=bin/$(DEMO_NAME)

$(DEMO_TGT):$(DEMO_OBJ) $(ENGINE_TGT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

demo:$(ENGINE_TGT)
demo:$(DEMO_TGT)
	./$(DEMO_TGT)



#test build

TEST_NAME=tests
TEST_SRC=$(wildcard src/tests/**/*.c src/tests/*.c)
TEST_HDR=$(wildcard tests/**/*.h tests/*.h)
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))
TEST_TGT=bin/$(TEST_NAME)

$(TEST_TGT):$(TEST_OBJ) $(ENGINE_TGT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

.PHONY:tests testdbg testvalgrind
tests: $(TEST_TGT)
	gtester --verbose $(TEST_TGT)


.PHONY: build
build:
	@mkdir -p lib
	@mkdir -p bin


.PHONY: clean
clean:
	rm -rf lib build bin $(ENGINE_OBJ) $(DEMO_OBJ) $(TEST_OBJ)
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#clang formatter command

FORMAT_OPTIONS=-style=Google
.PHONY: format
format:
	clang-format-3.3 -i $(FORMAT_OPTIONS) $(ENGINE_SRC) $(ENGINE_HDR)

.PHONY: check

		