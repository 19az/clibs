CC = g++
include ../../debugflags
EXE = unit_testing_c_ut
SRCS = unit_testing_c_ut.cpp ../unit_testing.cpp ../../rwfile/rwfile.cpp ../../strings/strings.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXE) $(OBJS)

