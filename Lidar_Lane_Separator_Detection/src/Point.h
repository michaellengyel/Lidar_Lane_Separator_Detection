//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef POINT
#define POINT

#include <iostream>

//============================================================================================================
// This class is a container for a 3D point
// algorithm.
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Point {
public:

	Point(const double xPos, const double yPos, const double zPos)
		: m_xPos(xPos), m_yPos(yPos), m_zPos(zPos)
	{

	}

	// Default constructor
	Point() {

	}

	// Default destructor
	~Point() {

	}

	const double m_xPos = 0;
	const double m_yPos = 0;
	const double m_zPos = 0;

	// TODO: Remove debug function "printPoint()"
	void printPoint() {
		std::cout.precision(17);
		std::cout << m_xPos << "\t" << m_yPos << "\t" << m_zPos << "\t" << std::endl;
	}
};

#endif