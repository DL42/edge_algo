CXXFLAGS=-std=c++11 -O2

all: trees_practice.o
	$(CXX) -o trees_practice trees_practice.o -Wl,-rpath,/Users/kevin/anaconda3/lib

clean:
	rm -f *.o
	rm -f trees_practice
