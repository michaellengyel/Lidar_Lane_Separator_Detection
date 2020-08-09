//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef DETECTOR
#define DETECTOR

#include <math.h>
#include <vector>

#include "Scan.h"
#include "Segment.h"
#include "Enumerations.h"

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Detector {
public:

	Detector(const Scan& scan) : m_scan(scan) {

		gridMaker();
		gridWeightSetter();
		gridFilter();
	}

	~Detector() {

	}

	void algorithm();

	std::vector<Segment> m_segments;


private:

	// Hough Space
	class Accumulator {
	public:

		static unsigned const int RO_RESOLUTION = 100; // Radius
		static unsigned const int THETA_RESOLUTION = 100; // Angle
		unsigned int m_accumulatorTable[RO_RESOLUTION][THETA_RESOLUTION];

	};

	// Space box container
	class GridBox {
	public:

		GridBox(double upperYLimit, double lowerYLimit, double upperXLimit, double lowerXLimit) :
			m_upperYLimit(upperYLimit),
			m_lowerYLimit(lowerYLimit),
			m_upperXLimit(upperXLimit),
			m_lowerXLimit(lowerXLimit)
		{
			m_xVector = ((upperXLimit + lowerXLimit) / 2);
			m_yVector = ((upperYLimit + lowerYLimit) / 2);
		}

		unsigned int m_weight = 0;

		double m_xVector;
		double m_yVector;

		const double m_upperYLimit;
		const double m_lowerYLimit;
		const double m_upperXLimit;
		const double m_lowerXLimit;

		bool filtered = false;
	};

	// Member container reference for Pulse data
	const Scan& m_scan;

	// Member container for grid boxes
	std::vector<GridBox> m_boxes;

	// The gridMaker divides the x-y plane into a grid of a parameterizable resolution
	// where the value of a given box is determined by the number of reflections contained
	// within it's borders.
	void gridMaker();

	// The gridWeightSetter iterates across all the boxes in the grid for all Pulses in
	// the Scan container and sets the weight of the box based on the number of points
	// inside the border of the box.
	void gridWeightSetter();

	// The gridFilter iterates across all the boxes in the grid and filters the ones whose
	// weight falls below some arbitrary treshold.
	void gridFilter();

	// The hough function implments the hough transform, which acts on the elements of the
	// grid similar to the way it would act on the pixels of an image.
	void hough();

	// Config parameters

	const double MAX_Y = static_cast<double>(algoParameters::MAX_Y);
	const double MIN_Y = static_cast<double>(algoParameters::MIN_Y);

	const double MAX_X = static_cast<double>(algoParameters::MAX_X);
	const double MIN_X = static_cast<double>(algoParameters::MIN_X);

	const double DELTA_Y = MAX_Y - MIN_Y;
	const double DELTA_X = MAX_X - MIN_X;

	const int NUMBER_OF_BOXES = 100; // Number of containers along the x and y axis

	const int FILTER_TRESHOLD = 30; // Weight of a box blow which it is filtered

};
#endif