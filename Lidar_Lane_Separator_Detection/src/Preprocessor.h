//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "IOHandler.h"
#include "Scan.h"

//============================================================================================================
// The Preprocessor is a precuresor to the algorithm. It understands the raw data coming from the sensor and
// filteres out the unneeded data. This may include fixing missing data points by used the 2nd return,
// filtering out the 2nd return, filtering out the points which are out of scope etc.
// The Preprocessor's job is filling the Scan data structure with the minimum valid data needed by the algo.
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Preprocessor {
public:
	
	Preprocessor(Scan& scan, IOHandler& ioHandler) {
		loadScan(scan, ioHandler);
	}

	Preprocessor() {

	}

	void loadScan(Scan& scan, IOHandler& ioHandler);

private:


};

#endif