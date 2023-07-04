CXX = g++

# fast
CXXFLAGS = -Wall -Wextra -O2 --static -std=c++17

# debug
CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: windowing

windowing: windowing.cpp range-tree-2d-id/2d.hpp range-tree-2d-id/2d.cpp  range-tree-2d-id/1d.hpp range-tree-2d-id/1d.cpp segtree-windowing-id/segtree.hpp segtree-windowing-id/segtree.cpp segtree-windowing-id/util.hpp


clean: 
	rm -f *.o

purge: clean
	rm -f windowing
