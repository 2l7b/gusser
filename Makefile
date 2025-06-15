CXX = g++
CXXFLAGS = -Wall -pthread -O2
TARGET = ges
SRC = ges.cpp

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
    rm -f $(TARGET)