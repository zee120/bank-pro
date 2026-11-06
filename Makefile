# Lightweight alternative to CMake for macOS and Linux.
CXX ?= c++
CXXFLAGS ?= -std=c++20
CPPFLAGS += -Iinclude -Isrc -Isrc/models -Isrc/screens \
            -Isrc/screens/auth -Isrc/screens/clients \
            -Isrc/screens/transactions -Isrc/screens/users

HEADERS := $(shell find include src -type f \( -name '*.h' -o -name '*.hpp' \))
TARGET := build/bank-pro

.PHONY: all run
all: $(TARGET)

$(TARGET): src/Main.cpp $(HEADERS) Makefile
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/Main.cpp -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)
