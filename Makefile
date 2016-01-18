CC := g++
CFLAGS := -Wall -std=c++98 -O2

GSLLIBS=gsl-config --libs
GSLCFLAGS=gsl-config --cflags

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))

TEST_FILES := src/DLA.cpp src/Walk.cpp src/tests/test_vector.cpp

walkrun: $(OBJ_FILES)
	$(CC) `$(GSLLIBS)` $^ -o $@

obj/%.o: src/%.cpp
	mkdir -p obj && $(CC) $(CFLAGS) `$(GSLCFLAGS)` $< -c -o $@


tests:
	$(CC) $(CFLAGS) `$(GSLCFLAGS)` `$(GSLLIBS)` $(TEST_FILES) -o runtests

clean:
	rm -rf walkrun runtests obj
