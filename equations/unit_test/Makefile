CC = g++
include ../../debugflags
EXE = equations_ut
SRCS = ../../rwfile/rwfile.cpp ../equations.cpp equations_ut.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJS)

