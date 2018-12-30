# PATHS - to search for the headers and source files
HEADERS_1 = ../core/ ../io/
HEADERS_2 =
HEADERS_3 =

SOURCE_1 = ../core/ ../io/
SOURCE_2 =
SOURCE_3 =

INCLUDES = $(HEADERS_1) $(HEADERS_2) $(HEADERS_3)
SOURCE = $(SOURCE_1) $(SOURCE_2) $(SOURCE_3)

vpath %.h $(INCLUDES)
vpath %.c $(SOURCE)

# COMPILER - with flags and libraries to link
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror $(foreach dir, $(INCLUDES), -I$(dir))
LDLIBS = -lm

# EXECUTABLE - the final binary file
BUILD_DIR = ./build
EXECUTABLES = $(BUILD_DIR)/run4 \
			  $(BUILD_DIR)/run8

# FILES
SHARED_HEADERS = emulator.h instructions.h debugger.h descriptions.h conversion.h files.h
SHARED_SOURCES = emulator.c instructions.c debugger.c descriptions.c conversion.c files.c
FOUR_HEADERS = run.h $(SHARED_HEADERS)
FOUR_SOURCES = run.c run4.c $(SHARED_SOURCES)
FOUR_OBJECTS := $(FOUR_SOURCES:%.c=$(BUILD_DIR)/%.o)
FOUR_DEPENDS = $(FOUR_OBJECTS:%.o=%.d)
EIGHT_HEADERS = run.h $(SHARED_HEADERS)
EIGHT_SOURCES = run.c run8.c $(SHARED_SOURCES)
EIGHT_OBJECTS := $(EIGHT_SOURCES:%.c=$(BUILD_DIR)/%.o)
EIGHT_DEPENDS = $(EIGHT_OBJECTS:%.o=%.d)

# TARGETS
.PHONY: all clean rebuild test

all: $(EXECUTABLES)

$(BUILD_DIR)/run4: $(FOUR_OBJECTS) $(FOUR_HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(FOUR_OBJECTS) $(LDLIBS) -o $(BUILD_DIR)/run4

-include $(FOUR_DEPENDS)

$(BUILD_DIR)/run8: $(EIGHT_OBJECTS) $(EIGHT_HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(EIGHT_OBJECTS) $(LDLIBS) -o $(BUILD_DIR)/run8

-include $(EIGHT_DEPENDS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(EXECUTABLES) $(FOUR_OBJECTS) $(EIGHT_OBJECTS)

rebuild: clean $(EXECUTABLES)

test:
	@echo "EXECUTABLES = ${EXECUTABLES}"
	@echo "OBJECTS = ${FOUR_OBJECTS} ${EIGHT_OBJECTS}"
