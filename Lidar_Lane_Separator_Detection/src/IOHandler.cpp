#include "IOHandler.h"

std::string IOHandler::readData(unsigned int column, unsigned int row) {

	// TODO: Put open file in in constructor
	std::ifstream inFile;
	inFile.open(m_inputFile);

	// Handle read issues
	if (!inFile) {
		std::cerr << "Unable to open file " << m_inputFile << std::endl;
		exit(1);
	}

	// TODO: Implement correct logic
	std::string str;
	int ctr = 0;
	while (std::getline(inFile, str, ',') && !(ctr == (column + row))) {
		std::cout << "running" << std::endl;
		ctr++;
	}

	// TODO: Put close file in destructor
	inFile.close();

	return str;
}