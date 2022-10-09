CC = g++
include ../../debugflags

EXE = unit_testing_c_ut
SOURCES = unit_testing_c_ut.cpp

INCLUDES_DIR = ../..
include $(INCLUDES_DIR)/unit_testing/Makefile
include $(INCLUDES_DIR)/rwfile/Makefile
include $(INCLUDES_DIR)/strings/Makefile

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -I$(INCLUDES_DIR)/ $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) -I$(INCLUDES_DIR)/ $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJECTS)

