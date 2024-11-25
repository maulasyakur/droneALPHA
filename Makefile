# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g

# Source, header, and target
SRC := Map.cpp Queue.cpp RoutePlanner.cpp Stack.cpp main.cpp
HEADERS := Map.h Queue.h RoutePlanner.h Stack.h
TARGET := DroneALPHA
STUDENT_NO := 2220356193
TEST_TARGET := TestBuild
TEST_SRC := Map.cpp Queue.cpp RoutePlanner.cpp Stack.cpp Test.cpp

# Arguments for running the program
ARGS := 250 5 distance_data.csv priority_provinces.txt weather_restricted_provinces.txt

# Build target
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Test target
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

# Run with arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Run test
run_test: $(TEST_TARGET)
	./$(TEST_TARGET) $(ARGS)

# Run with valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) $(ARGS)

# Run with gdb
gdb: $(TARGET)
	gdb --args ./$(TARGET) $(ARGS)

# Clean build files
clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Create a zip file including source and headers
zip: $(TARGET)
	zip b$(STUDENT_NO).zip Map.cpp Queue.cpp RoutePlanner.cpp Stack.cpp $(HEADERS) -0

# Phony targets
.PHONY: all clean valgrind gdb run zip