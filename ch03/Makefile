CXX      = g++
CXXFLAGS = -std=c++14 -g -Wall -Wextra \
-Wno-parentheses \
-Wno-unused-local-typedefs \
-Wno-write-strings

INCLUDES = -Iinclude \
-I/usr/include/python2.7 \
-I../matplotlib-cpp \
-I../xtensor/include \
-I../xtensor-blas/include \
-I../xtensor-blas/include/xtensor-blas/flens

TGTS   = `ls test/test_*.cc | sed -e s/.cc//`
TGT   ?= test/test_softmax
#TGT   ?= test/test_three_layer_net
#TGT   ?= test/test_step_function
#TGT   ?= test/test_relu
#TGT   ?= test/test_sigmoid
#SRCS  =
SRCS += $(TGT).cc
BIN   = $(TGT)
OBJS  = $(SRCS:.cc=.o)
LIBS  = -lpython2.7

all: compile_all

compile: $(BIN)

compile_all:
	@for target in $(TGTS); do \
	make TGT=$${target} compile; \
	done

test: $(BIN)
	./$(BIN)

test_all:
	@for target in $(TGTS); do \
	make TGT=$${target} test; \
	done

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $@ $(LIBS)

.cc.o: $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BIN) $(OBJS)

clean_all:
	@for target in $(TGTS); do \
	make TGT=$${target} clean; \
	done

.PHONY: all compile compile_all test test_all clean clean_all
