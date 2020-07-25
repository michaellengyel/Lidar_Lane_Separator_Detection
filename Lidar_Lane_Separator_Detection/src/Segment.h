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

	const Point m_start;
	const Point m_end;

};

#endif