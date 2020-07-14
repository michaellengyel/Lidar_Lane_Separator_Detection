//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef IO_HANDLER
#define IO_HANDLER

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class IOHandler {
public:

	IOHandler(std::string inputFile) : m_inputFile(inputFile) {

		// TODO: Put open file in in constructor
		m_inFile.open(m_inputFile);

		// Handle read issues
		if (!m_inFile) {
			std::cerr << "Unable to open file " << m_inputFile << std::endl;
			exit(1);
		}
	}

	~IOHandler() {

		// TODO: Put close file in destructor
		m_inFile.close();
	}

	std::string readData(char delimeter);

private:

	std::string m_inputFile;
	std::ifstream m_inFile;

};

#endif