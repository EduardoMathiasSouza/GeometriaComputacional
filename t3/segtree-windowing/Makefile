CXX = g++

# fast
CXXFLAGS = -Wall -Wextra -O2 --static -std=c++17

# debug
CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: segtree segtree-brute gen-segtree

segtree: segtree.cpp util.hpp

segtree-brute: segtree-brute.cpp

gen-segtree: gen-segtree.cpp

clean:

purge: clean
	-rm -f segtree-brute segtree gen-segtree
