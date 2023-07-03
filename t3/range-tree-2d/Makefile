CXX = g++

# fast
CXXFLAGS = -Wall -Wextra -O2 --static -std=c++17

# debug
CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: 2d 2d-brute

2d: 2d.cpp 1d.o

1d.o: 1d.cpp 1d.hpp

2d-brute: 2d-brute.cpp

clean: 
	rm -f *.o

purge: clean
	1d 2d-brute 2d
