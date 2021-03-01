#Ivan Stus - 821201908
#Kenny Kieu - 819180993
#CS 570-05
#Spring 2021
#Assignment #1 - ls command 

# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
myls : myls.o
	$(CXX) $(CXXFLAGS) -o myls $^
myls.o : myls.c

clean :
	rm *.o

