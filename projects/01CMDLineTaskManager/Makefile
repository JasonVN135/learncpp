CXX = g++
CXXFLAGS = -std=c++20 -Wextra -Wshadow
# -std=c++20 -Wall -Werror -Wextra -Wshadow

output: main.o task_manager.o file_manager.o
	$(CXX) $(CXXFLAGS) main.o task_manager.o file_manager.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

task_manager.o: task_manager.cpp task_manager.h
	$(CXX) $(CXXFLAGS) -c task_manager.cpp

file_manager.o: file_manager.cpp file_manager.h
	$(CXX) $(CXXFLAGS) -c file_manager.cpp

clean:
	rm *.o main