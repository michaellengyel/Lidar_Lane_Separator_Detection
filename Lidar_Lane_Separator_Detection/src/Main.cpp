#include <iostream>

#include "IOHandler.h"
#include "Scan.h"
#include "Preprocessor.h"
#include "Detector.h"
#include "Visualization.h"

int main() {

	// Declaring data container and handling classes
	IOHandler ioHandler("res/3.csv");
	Scan scan;

	// Declaring data processing classes
	Preprocessor preprocessor(scan, ioHandler);
	Detector detector(scan);

	// Declaring data and results visualization classes
	Visualization visualization(scan);

	return 0;
}