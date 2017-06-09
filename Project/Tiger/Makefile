CXX = g++
CXXSTD = -std=c++14
CXXFLAG = $(CXXSTD)
CXXOBJFLAG = -c

CLEANLIST = $(OBJ_PATH)/* \
			$(SRC_PATH)/scanner.cpp \
			$(SRC_PATH)/parser.h \
			$(SRC_PATH)/parser.cpp \
			$(SRC_PATH)/parser.output

AUXCLEANLIST = 	$(SRC_PATH)/stack.hh \
				$(SRC_PATH)/location.hh \
				$(SRC_PATH)/position.hh

BIN_PATH = bin
OBJ_PATH = obj
SRC_PATH = src
TEST_PATH = test
BISON_SUB_PATH = bison
FLEX_SUB_PATH = flex

SRC = $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))


tiger: $(OBJ)
	$(CXX) $(CXXSTD) -o $(BIN_PATH)/tiger Tiger.cpp $?

# test: $(OBJ)
# 	$(CXX) $(CXXSTD) -o $(TEST_PATH)/test $(TEST_PATH)/test.cpp $?
# 	cd test && ./unit_test.sh

# parser_unit_test:
# 	cd test && ./unit_test.sh	

objs: bison flex $(OBJ)
	@echo $?

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAG) $(CXXOBJFLAG) -o $@ $<

.PHONY: bison
bison: $(SRC_PATH)/$(BISON_SUB_PATH)/parser.yy
	bison -d -v \
	--defines=$(SRC_PATH)/parser.h \
	--output=$(SRC_PATH)/parser.cpp \
	$<

.PHONY: flex
flex: $(SRC_PATH)/$(FLEX_SUB_PATH)/scanner.l
	flex -o $(SRC_PATH)/scanner.cpp $<


.PHONY: clean
clean:
	-rm -f $(CLEANLIST)

.PHONY: cleanall
cleanall:
	-rm -f $(CLEANLIST) $(AUXCLEANLIST)