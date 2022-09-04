CC = g++
include ../../debugflags
EXE = equations_ut
SRCS = equations_ut.cpp ../equations.cpp ../../unit_testing/unit_testing.cpp ../../rwfile/rwfile.cpp ../../strings/strings.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJS)

