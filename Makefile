CC = gcc
CXX = g++
CXXFLAGS = -march=native -O2 -fmessage-length=0 -Wall
CXXSTDFLAGS = -std=c++14 -pipe
LDFLAGS =
OBJS = pid.o process.o swap.o swapusage.o
LIBS = 
TARGET = swapusage

%.o: %.cpp
	$(CXX) $(CXXSTDFLAGS) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *~

depend:
	makedepend -Y *.c *.cpp 2>/dev/null
	rm Makefile.bak

# DO NOT DELETE

pid.o: pid.h
process.o: pid.h process.h swap.h
swap.o: swap.h
swapusage.o: pid.h process.h swap.h
