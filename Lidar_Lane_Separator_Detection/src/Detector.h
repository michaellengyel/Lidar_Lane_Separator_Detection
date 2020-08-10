//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef DETECTOR
#define DETECTOR

#include <math.h>
#include <vector>
#include <iterator>

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

	}

	~Detector() {

	}

	void algorithm();

	std::vector<Segment> m_segments;


private:

	// Config Parameters

	const double MAX_Y = static_cast<double>(algoParameters::MAX_Y);
	const double MIN_Y = static_cast<double>(algoParameters::MIN_Y);

	const double MAX_X = static_cast<double>(algoParameters::MAX_X);
	const double MIN_X = static_cast<double>(algoParameters::MIN_X);

	const double DELTA_Y = MAX_Y - MIN_Y;
	const double DELTA_X = MAX_X - MIN_X;

	const int NUMBER_OF_BOXES = 100; // Number of containers along the x and y axis

	const int FILTER_TRESHOLD = 30; // Weight of a box blow which it is filtered

	const int HOUGH_TRESHOLD = 30; // Weight above which a point in the hough table is considered

	static unsigned const int RHO_RESOLUTION = 500; // Radius
	static unsigned const int THETA_RESOLUTION = 359; // Angle (360 degrees with 0 = 360, thus 359)

	const double PI = 3.14159265;
	const double SQRTWO = 1.41421356;

	// End Config Parameters

	// Private Variables for accumulatorNormalizer() function
	// End Private Variables for accumulatorNormalizer() function

	// Hough Space
	class Accumulator {
	public:

		//int m_accumulatorTable[RHO_RESOLUTION][THETA_RESOLUTION];

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
			m_xCoord = ((upperXLimit + lowerXLimit) / 2);
			m_yCoord = ((upperYLimit + lowerYLimit) / 2);
		}

		// Copy constructor
		GridBox(const GridBox &p) {
			m_weight = p.m_weight;
			m_xCoord = p.m_xCoord;
			m_yCoord = p.m_yCoord;
			m_upperYLimit = p.m_upperYLimit;
			m_lowerYLimit = p.m_lowerYLimit;
			m_upperXLimit = p.m_upperXLimit;
			m_lowerXLimit = p.m_lowerXLimit;
		}

		// Assignment operator overloading
		GridBox& operator = (const GridBox& rhs) {
			m_weight = rhs.m_weight;
			m_xCoord = rhs.m_xCoord;
			m_yCoord = rhs.m_yCoord;
			m_upperYLimit = rhs.m_upperYLimit;
			m_lowerYLimit = rhs.m_lowerYLimit;
			m_upperXLimit = rhs.m_upperXLimit;
			m_lowerXLimit = rhs.m_lowerXLimit;
			return *this;
		}

		unsigned int m_weight = 0;

		double m_xCoord;
		double m_yCoord;

		double m_upperYLimit;
		double m_lowerYLimit;
		double m_upperXLimit;
		double m_lowerXLimit;

	};

	// Member container reference for Pulse data
	const Scan& m_scan;

	// Member container for grid boxes
	std::vector<GridBox> m_boxes;

	// Accumulator container (TODO: Refactor)
	//int m_accumulatorTable[550][355];
	//std::array<std::array<int, RHO_RESOLUTION>, THETA_RESOLUTION> m_accumulatorTable;

	// Results container


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

	// The accumulatorNormalizer function tansforms the rho value, with a range of
	// [(-sqrt(2) * MAX_Y) to (sqrt(2) * MAX_Y)] into a range of [0-1000]. In this respect
	// it is some type of normalization. This is a helper functon for hough().
	int accumulatorNormalizer(double rho);

	// The dimensionConverter maps a 2D array's key to a 1D array's key.
	int dimensionConverter(int i, int j, int iSize, int jSize);

	// The filterTopIntersects function finds the peek points in the accumulator grid. This is
	// a helper function for the hough() function.
	void filterTopIntersects(std::vector<int> &accumulatorTable);

};
#endif