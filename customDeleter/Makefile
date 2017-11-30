CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Weffc++

all: CXXFLAGS += -O3 -fno-omit-frame-pointer
all: customDeleter

debug: CXXFLAGS += -DDEBUG -g
debug: customDeleter

clean:
	rm -f customDeleter

customDeleter: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o customDeleter 
