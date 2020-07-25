//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef SEGMENT
#define SEGMENT

#include "Point.h"

//============================================================================================================
// This class is a container for a 3D line or segment. This one or more of these shall be the output of the
// algorithm.
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Segment {
public:

	Segment(Point start, Point end) : m_start(start), m_end(end) {

	}

	// Default constructor
	Segment() {

	}

	// Default destructor
	~Segment() {

	}

	// Copy constructor
	Segment(const Segment &s) {
		m_start = s.m_start;
		m_end = s.m_end;
	}

	// Assignment operator overloading
	Segment& operator = (const Segment& rhs) {
		m_start = rhs.m_start;
		m_end = rhs.m_end;
		return *this;
	}
	

	Point m_start;
	Point m_end;

};

#endif