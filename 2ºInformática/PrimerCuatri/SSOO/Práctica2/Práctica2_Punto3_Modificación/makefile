CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -Wpedantic \
           -Wshadow -Wnon-virtual-dtor -Wold-style-cast \
           -Wcast-align -Wunused -Woverloaded-virtual \
           -Wconversion -Wsign-conversion -Wnull-dereference \
           -Wdouble-promotion -Wformat=2 -Wmisleading-indentation \
           -Wduplicated-cond -Wduplicated-branches -Wlogical-op \
           -Wuseless-cast

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
EXECUTABLE = docserver

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)

.PHONY: clean

run: $(EXECUTABLE)
	./$(EXECUTABLE)