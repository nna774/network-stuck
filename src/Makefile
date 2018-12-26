TARGET := main
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
RM := rm -fr

all: $(TARGET)
$(TARGET): http.o

clean:
	$(RM) *.o $(TARGET)

.PHONY: clean
