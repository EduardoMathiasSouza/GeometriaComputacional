CXX = g++

# fast
CXXFLAGS = -Wall -Wextra -O2 --static -std=c++17

# debug
#CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: main segtree-brute teste gen

main: main.cpp segtree.o util.hpp

segtree.o: segtree.hpp segtree.cpp util.hpp

segtree-brute: segtree-brute.cpp util.hpp

teste: teste.cpp util.hpp

gen: gen.cpp

clean:
	-rm *.o

purge: clean
	-rm -f segtree-brute main gen teste
