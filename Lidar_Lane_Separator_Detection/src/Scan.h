//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef SCAN
#define SCAN

#include <vector>
#include <iostream>

#include "Point.h"

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
	class Pulse {
	public:

		Pulse(const Point& point, const double luminosity, const double distance)
			: m_point(point), m_luminosity(luminosity), m_distance(distance)
		{

		}

		Pulse(const Point point)
			: m_point(point)
		{

		}

		~Pulse() {

		}

		const Point m_point;
		const double m_luminosity = 0;
		const double m_distance = 0;

		// TODO: Remove debug function "printPulse()"
		void printPulse() {
			std::cout.precision(17);
			std::cout << m_point.m_xPos << "\t" << m_point.m_yPos << "\t" << m_point.m_zPos << "\t" << std::endl;
		}
	};

	// Member data structure holding Laser Pulses
	std::vector<Pulse> m_data;

};

#endif
