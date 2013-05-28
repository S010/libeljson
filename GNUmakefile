CXX=g++
AR=ar
#CXX=clang++

CXXFLAGS+=-Wall
CXXFLAGS+=-std=c++11
CXXFLAGS+=-O2
CXXFLAGS+=-Iinclude

LDFLAGS+=-Llib

all: lib/ lib/libeljson.so

lib/:
	mkdir -p $@

lib/libeljson.so: src/json.o src/parse.o
	$(CXX) -fPIC -shared -Wl,-soname,libeljson.so $^ -o $@

src/json.o: src/json.cpp include/json.hpp
	$(CXX) -fPIC $(CXXFLAGS) -c src/json.cpp -o $@

src/parse.o: src/parse.cpp include/json.hpp
	$(CXX) -fPIC $(CXXFLAGS) -c src/parse.cpp -o $@

test: all test/test
	env LD_LIBRARY_PATH=lib test/test

test/test: test/big.json test/test.o
	$(CXX) $(LDFLAGS) -leljson test/test.o -o $@

test/big.json:
	gunzip test/big.json.gz

clean:
	rm -rf src/*.o lib/ test/*.o test/test test/test2

distclean:
	gzip test/big.json
