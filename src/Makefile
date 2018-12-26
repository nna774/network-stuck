all: build

TARGET := main
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
RM := rm -fr
SRCS := main.cpp http.cpp
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(SRCS:%.cpp=%.d)
-include $(DEPS)

build: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -MP $<

clean:
	$(RM) *.o $(TARGET) $(DEPS)

.PHONY: clean
