CXX = g++
CXXFLAGS = -std=c++20 -Wall

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
EXECUTABLE = ejecutable

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
