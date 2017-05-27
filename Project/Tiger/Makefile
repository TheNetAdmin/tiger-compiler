CXX = g++
CXXSTD = -std=c++14

CLEANLIST = $(addsuffix .o, $(OBJ)) \
			scanner.cc \
			stack.hh *.output \
			*.tab.* *.hh

scanner: scanner.l error.h
	flex -o scanner.cc $<
	# $(CXX) $(CXXSTD) -c -o scanner.o scanner.cc

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)