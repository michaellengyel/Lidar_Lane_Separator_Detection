//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef DETECTOR
#define DETECTOR

#include "Scan.h"
#include "Segment.h"

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Detector {
public:

	Detector(const Scan& scan) : m_scan(scan) {

	}

	~Detector() {

	}

	void algorithm();

	std::vector<Segment> m_segments;


private:

	const Scan& m_scan;

};

#endif