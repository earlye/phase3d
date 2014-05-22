SOURCE_MODULES=$(shell find main -name "*.cpp")
TEST_MODULES=$(shell find test -name "*_test.cpp")
TEST_LOGS=$(patsubst %.cpp,%.log,$(TEST_MODULES))
CXXFLAGS+=-Imain/cpp

$(info SOURCE_MODULES:$(SOURCE_MODULES))
$(info TEST_MODULES:$(TEST_MODULES))
$(info TEST_LOGS:$(TEST_LOGS))

all : test

clean :

test : $(TEST_LOGS)

%.log : %.exe Makefile
	$< 2>&1 | tee $@

%.exe : %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MD -c -o $@ $<

-include $(SOURCE_MODULES:.cpp=.d) $(TEST_MODULES:.cpp=.d)