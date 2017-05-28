CXX = g++
CXXSTD = -std=c++14

CLEANLIST = *.o \
			scanner.cpp parser.h parser.cpp \
			stack.hh location.hh position.hh *.output \
			*.tab.* stack.hh

test: test.cpp driver
	$(CXX) $(CXXSTD) -o test test.cpp driver.o parser.o scanner.o

driver: driver.h parser scanner
	$(CXX) $(CXXSTD) -c -o driver.o driver.cpp

parser: parser.yy
	bison -d -v --defines=parser.h --output=parser.cpp parser.yy
	$(CXX) $(CXXSTD) -c -o parser.o parser.cpp

scanner: scanner.l parser
	flex -o scanner.cpp scanner.l
	$(CXX) $(CXXSTD) -c -o scanner.o scanner.cpp

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)