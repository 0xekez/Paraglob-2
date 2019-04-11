LIBNAME := ahocorasick
BUILD_DIRECTORY := build/
LIB_TARGET := $(BUILD_DIRECTORY)lib$(LIBNAME).a
HEADER_FILES := $(wildcard *.h)
OBJECT_FILES := $(addprefix $(BUILD_DIRECTORY),$(patsubst %.c,%.o,$(wildcard *.c)))
CFLAGS := -Wall -O2
COMPILER := gcc
AR := ar -cvq
.PHONY : clean

# On Mac need to create the lib using a different command
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
AR := libtool -static -o
endif

all: $(LIB_TARGET) clean

$(LIB_TARGET): $(BUILD_DIRECTORY) $(OBJECT_FILES)
	$(AR) $(LIB_TARGET) $(OBJECT_FILES)

$(BUILD_DIRECTORY)%.o: %.c $(HEADER_FILES)
	$(COMPILER) -o $@ -c $< $(CFLAGS)

$(BUILD_DIRECTORY):
	@mkdir -p $(BUILD_DIRECTORY)

clean:
	rm -rf $(OBJECT_FILES)
