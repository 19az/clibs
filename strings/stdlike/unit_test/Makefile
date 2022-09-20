CC = g++
include debugflags
EXE = stdlike_strings_ut
SOURCES = stdlike_strings_ut.cpp
INCLUDES_DIR = ../../..
include $(INCLUDES_DIR)/strings/stdlike/Makefile

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJECTS)

