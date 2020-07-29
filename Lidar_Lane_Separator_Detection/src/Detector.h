//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef DETECTOR
#define DETECTOR

#include "Scan.h"
#include "Segment.h"

#include <vector>
#include <algorithm>
#include <functional>

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

	Segment m_segment;

private:

	void cluster();

	void slidingWindow_1();
	void slidingWindow_2();
	double m_frontLeft = 0;
	double m_RearLeft = 0;

	const Scan& m_scan;

	// Holds y-axis point data of frontal section
	std::vector<double> m_xFrontRight;
	// Holds y-axis point data of rear section
	std::vector<double> m_xRearRight;
	// Holds y-axis point data of frontal section
	std::vector<double> m_xFrontLeft;
	// Holds y-axis point data of rear section
	std::vector<double> m_xRearLeft;

	// Config parameters

	const double FRONT_MIN = 0;
	const double FRONT_MAX = 30;

	const double REAR_MAX = 0;
	const double REAR_MIN = -30;

	const double SENSOR_Z = 2.3;

};

#endif