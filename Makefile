#*******************************************************************************
#Name            : Makefile
#Author          : Sean Alling
#Version         : V1.0
#Copyright       : 2015
#Creation Date   : 11/19/2015
#*******************************************************************************/
CXX = g++
CXXFLAGS = -MD -MP -pedantic -Wall -std=c++11 -Wextra 
CXXSRC = $(wildcard *.cpp)
EXE = scriptgen


$(EXE):$(CXXSRC:%.cpp=%.o)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(CXXSRC:.cpp=.o)

-include $(CXXSRC:.cpp=.d)


clean:
	-rm $(CXXSRC:%.cpp=%.o) $(CXXSRC:%.cpp=%.d) $(EXE)

test:
	./test.sh

remake: clean $(EXE)