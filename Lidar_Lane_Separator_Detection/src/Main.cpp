#include <iostream>

#include "IOHandler.h"

int main() {

	std::cout << "Hello World" << std::endl;

	IOHandler ioHandler("res/2.csv");

	std::string s = ioHandler.readData(9, 1);
	std::cout << s << std::endl;

	return 0;
}