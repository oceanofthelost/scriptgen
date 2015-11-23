#*******************************************************************************
#Name            : Makefile
#Author          : Sean Alling
#Version         : V1.0
#Copyright       : 2015
#Creation Date   : 11/19/2015
#*******************************************************************************/
CXX := g++
CXXFLAGS := -pedantic -Wall -std=c++11 -Wextra 
CXXSRC := $(wildcard ./source/*.cpp)
SOURCEDIR := ./source
USEROPTIONS := ./settings/ 
#OFMESSAGE := ./OFMessages
OFMESSAGE := ./Generator
INCLUDE := -I $(USEROPTIONS) -I $(OFMESSAGE) -I $(SOURCEDIR)
CXXOBJ := $(patsub %.cpp, %.o, $(CXXOBJ))
EXE := scriptgen





$(EXE):$(CXXSRC)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(CXXSRC) $(INCLUDE)

generate: ./Generator/fileGenerator.cpp
	$(CXX) $(CXXFLAGS) -o ./Generator/generate ./Generator/fileGenerator.cpp $(INCLUDE)
	-./Generator/generate

clean:
	-@rm $(EXE) *.d ./Generator/*.hpp > /dev/null  2>&1 ||:

remake: clean $(EXE)