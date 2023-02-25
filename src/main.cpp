#include "Puzzle.hpp"

#include <string>
#include <iostream>
#include <cstdlib>

void error(std::string message, int code)
{
	std::cerr << message << std::endl;
	std::exit(code);
}

int main()
{
	Puzzle puzzle(3);
	std::cout << puzzle << std::endl;
}
