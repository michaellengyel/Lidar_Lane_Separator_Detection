#include <iostream>

#include "IOHandler.h"
#include "Scan.h"
#include "Preprocessor.h"
#include "Detector.h"
#include "Visualization.h"

int main() {

	// Declaring data container and handling classes
	IOHandler ioHandler("res/2.csv");
	Scan scan;

	// Declaring data processing classes
	Preprocessor preprocessor(scan, ioHandler);
	Detector detector(scan);

	// Declaring data and results visualization classes
	Visualization visualization(scan);


	std::string s = ioHandler.readData(9, 1);
	std::cout << s << std::endl;

	return 0;
}