//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef IO_HANDLER
#define IO_HANDLER

#include <iostream>
#include <string>
#include <fstream>
#include <string>

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

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

#endif