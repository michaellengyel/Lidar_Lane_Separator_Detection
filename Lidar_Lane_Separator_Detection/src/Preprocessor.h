//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef PREPROCESSOR
#define PREPROCESSOR

#include "Enumerations.h"
#include "IOHandler.h"
#include "Point.h"
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

	void filterData(Scan& scan, std::string blocks[]);

	void trackDuplicate(std::string blocks[]);

	// Input file config parameters
	const unsigned int m_columnX = static_cast<unsigned int>(dataFormatA::COLUMN_X);
	const unsigned int m_columnY = static_cast<unsigned int>(dataFormatA::COLUMN_Y);
	const unsigned int m_columnZ = static_cast<unsigned int>(dataFormatA::COLUMN_Z);
	const unsigned int m_columnDistance = static_cast<unsigned int>(dataFormatA::DISTANCE);
	const unsigned int m_columnIntensity = static_cast<unsigned int>(dataFormatA::INTENSITY);
	const unsigned int m_columnLaserID = static_cast<unsigned int>(dataFormatA::LASER_ID);

	const bool filterDuplicateReturn = g_filterDuplicateReturn;

	// Input data config parameters
	const unsigned int minDistance = static_cast<unsigned int>(algoParameters::MIN_DISTANCE);
	const unsigned int maxDistance = static_cast<unsigned int>(algoParameters::MAX_DISTANCE);
	const unsigned int minIntensity = static_cast<unsigned int>(algoParameters::MIN_INTENSITY);
	const unsigned int maxIntensity = static_cast<unsigned int>(algoParameters::MAX_INTENSITY);

	// Defines which duplicate frame to use (currently 0, 1 available)
	const unsigned int m_usedDuplicate = static_cast<unsigned int>(algoParameters::USED_DUPLICATE);
	const unsigned int m_numberOfDuplicate = static_cast<unsigned int>(algoParameters::NUMBER_OF_DUPLICATES);

	bool m_readingDuplicate = false;
	int m_previousID = 0;
	int m_duplicateCounter = 0;
};

#endif