//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef SCAN
#define SCAN

#include <vector>

//============================================================================================================
// This class is the data final, filtered data structure on which any and all algorithms will operate. This
// data structure will be filled by a filtering algo, which will decide which data is needed and which is
// filtered. This class is intended to be passed to the detection algorithms via reference
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Scan {
public:

	Scan() {

	}

	~Scan() {

	}

private:

	// Member class for holding the point data
	class Point {
	public:

		Point(const int xPos, const int yPos, const int zPos, const int luminosity)
			: m_xPos(xPos), m_yPos(yPos), m_zPos(zPos), m_luminosity(luminosity)
		{

		}

		~Point() {

		}

		const int m_xPos = 0;
		const int m_yPos = 0;
		const int m_zPos = 0;
		const int m_luminosity = 0;
	};

	// Member data structure holding Points
	std::vector<Point> m_data;

};

#endif
