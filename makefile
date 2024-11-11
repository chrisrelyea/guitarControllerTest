# Makefile for building guitar.cpp with HIDAPI

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2

# Executable and source file
TARGET = guitar
SRC = guitar.cpp

# Link with hidapi
# Adjust the library and include paths as necessary for your system
# LIBS = -lhidapi-libusb # Alternative for Linux using libusb backend
LIBS = -lhidapi        # For macOS (Homebrew installs hidapi as -lhidapi)
# LIBS = -lhidapi -lsetupapi # For Windows (assuming hidapi.dll is available)

# Build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean up
.PHONY: clean
clean:
	rm -f $(TARGET)
