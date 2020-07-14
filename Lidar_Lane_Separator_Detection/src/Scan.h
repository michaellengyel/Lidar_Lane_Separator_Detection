//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef SCAN
#define SCAN

#include <vector>
#include <iostream>

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

	// Member class for holding the point data
	class Point {
	public:

		Point(const double xPos, const double yPos, const double zPos, const double luminosity)
			: m_xPos(xPos), m_yPos(yPos), m_zPos(zPos), m_luminosity(luminosity)
		{

		}

		Point(const double xPos, const double yPos, const double zPos)
			: m_xPos(xPos), m_yPos(yPos), m_zPos(zPos)
		{

		}

		~Point() {

		}

		const double m_xPos = 0;
		const double m_yPos = 0;
		const double m_zPos = 0;
		const double m_luminosity = 0;

		void printPoint() {
			std::cout.precision(17);
			std::cout << m_xPos << "\t" << m_yPos << "\t" << m_zPos << "\t" << std::endl;
		}
	};

	// Member data structure holding Points
	std::vector<Point> m_data;

};

#endif
