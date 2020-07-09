#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <string>

class IOHandler {
public:

	IOHandler(std::string inputFile) : m_inputFile(inputFile) {

	}

	~IOHandler() {

	}

	std::string readData(unsigned int column, unsigned int row);

private:

	std::string m_inputFile;

};