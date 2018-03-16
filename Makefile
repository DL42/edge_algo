CXXFLAGS=-std=c++11 -O2

all: trees_practice.o trees_practice_uncoalesced.o trees_practice_multiple_uncoalesced.o count_mnodes.o
	echo $(CXX)
	$(CXX) -o trees_practice trees_practice.o count_mnodes.o -Wl,-rpath,/Users/kevin/anaconda3/lib
	$(CXX) -o trees_practice_uncoalesced trees_practice_uncoalesced.o count_mnodes.o -Wl,-rpath,/Users/kevin/anaconda3/lib
	$(CXX) -o trees_practice_multiple_uncoalesced trees_practice_multiple_uncoalesced.o count_mnodes.o -Wl,-rpath,/Users/kevin/anaconda3/lib

trees_practice.o: edge.hpp count_mnodes.hpp
trees_practice_uncoalesced.o: edge.hpp count_mnodes.hpp
trees_practice_multiple_uncoalesced.o: edge.hpp count_mnodes.hpp

clean:
	rm -f *.o
	rm -f trees_practice
