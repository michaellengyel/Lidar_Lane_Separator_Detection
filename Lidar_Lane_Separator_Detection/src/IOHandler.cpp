#include "IOHandler.h"

std::string IOHandler::readData(char delimeter) {

	std::string str;

	if (std::getline(m_inFile, str, delimeter)) {

	}
	else {
		return "EOF";
	}

	return str;
}