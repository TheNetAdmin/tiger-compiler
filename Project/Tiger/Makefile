CXX = g++
CXXSTD = -std=c++14

CLEANLIST = $(addsuffix .o, $(OBJ)) \
			scanner.cc \
			stack.hh location.hh position.hh *.output \
			*.tab.* stack.hh

parser: parser.yy
	bison -d -v parser.yy
	# $(CXX) $(CXXSTD) -c -o parser.o parser.tab.cc

scanner: scanner.l error.h
	flex -o scanner.cc $<
	# $(CXX) $(CXXSTD) -c -o scanner.o scanner.cc

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)