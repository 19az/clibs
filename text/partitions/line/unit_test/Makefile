CC = g++
include debugflags
EXE = line_ut
SOURCES = line_ut.cpp
INCLUDES_DIR = ../../../..
include $(INCLUDES_DIR)/text/partitions/line/Makefile
include $(INCLUDES_DIR)/unit_testing/Makefile

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJECTS) 
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJECTS)

