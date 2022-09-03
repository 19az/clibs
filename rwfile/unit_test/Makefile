CC = g++
include ../../debugflags
EXE = rwfile_ut
SRCS = ../rwfile.cpp rwfile_ut.cpp ../../strings/strings.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJS)

