# Compiler
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -stdlib=libc++

# Targets
TARGET = mytests
OBJECTS = mytests.o  # Remove customexceptions.o since it's not needed

# Main target to build the test executable
all: $(TARGET)

# Link all object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile the test file
mytests.o: mytests.cpp BST.hpp BSTNode.hpp customexceptions.hpp
	$(CXX) $(CXXFLAGS) -c mytests.cpp

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJECTS)
