CXX=g++
TARGET=qam16
SOURCES=main.cpp

LFLAGS=-std=c++17

OBJSC=$(SOURCES:.c=.o)
OBJS=$(OBJSC:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) -m -b "0000111100001111"

purge: clean
	rm -f $(TARGET)

clean:
	rm -f *.o