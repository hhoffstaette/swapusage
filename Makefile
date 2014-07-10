CC = gcc
CXX = g++
CXXFLAGS = -std=c++11 -pipe -march=native -O2 -fmessage-length=0 -Wall
LDFLAGS =
OBJS = Matcher.o pid.o process.o swap.o substring.o swapusage.o 
LIBS = 
TARGET = swapusage

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *~

depend:
	makedepend -Y *.c *.cpp 2>/dev/null
	rm Makefile.bak

# DO NOT DELETE

Matcher.o: Matcher.h
pid.o: Matcher.h pid.h
process.o: pid.h process.h swap.h
substring.o: substring.h
swap.o: swap.h substring.h
swapusage.o: pid.h process.h swap.h
