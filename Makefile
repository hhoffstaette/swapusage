CC = gcc
CXX = g++
CXXFLAGS = -std=c++11 -pipe -march=native -O2 -fmessage-length=0 -Wall
LDFLAGS =
OBJS = swapusage.o process.o swap.o substring.o
LIBS = 
TARGET = swapusage
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
