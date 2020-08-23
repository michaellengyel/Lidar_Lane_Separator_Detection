//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef DETECTOR
#define DETECTOR

#include "Enumerations.h"
#include "Scan.h"
#include "Segment.h"

#include <algorithm>
#include <functional>
#include <vector>

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Detector {
public:
  Detector(const Scan &scan) : m_scan(scan) { init(); }

  ~Detector() {}

  void algorithm();

  std::vector<Segment> m_segments;

private:
  // Space box container
  class SpaceBox {
  public:
    SpaceBox(int upperLimit, int lowerLimit)
        : m_upperLimit(upperLimit), m_lowerLimit(lowerLimit) {}

    std::vector<double> m_xPoints;

    double m_yCoord = 0; // Stores the first found point of density (y)
    double m_xCoord = 0; // Stores the boxes middle as a coord (x)

    double m_boxAverage;

    int m_upperLimit;
    int m_lowerLimit;
  };

  // Space box containers
  std::vector<SpaceBox> m_spaceBoxsLeft;
  std::vector<SpaceBox> m_spaceBoxsRight;

  // This function creates and inititalzes a fixed number of SpaceBox objects
  // which it then adds to the spaceBoxs vector
  void init();

  // The cluster function sorts all the x (perpendicular) values of all Pulses
  // stored in a Scan, into individual vector containers representing a box in
  // space. The number of boxes should be a configurable value.
  void cluster();

  // Slides across the x-axis of all 3D points and looks for regions of higher
  // then average density
  void slidingWindow(std::vector<SpaceBox> &box);

  // calculates the average density of a given box
  double boxAverage(std::vector<double> &box);

  // Creates renderable segments from the left and right spaceBox containers by
  // restructuring them
  void segmentMaker();

  // Results (Right side)
  double m_frontRight = 0;
  double m_RearRight = 0;

  // Results (Left side)
  double m_frontLeft = 0;
  double m_RearLeft = 0;

  const Scan &m_scan;

  // Config parameters
  const double FRONT_MIN = 0;
  const double FRONT_MAX = static_cast<double>(algoParameters::MAX_Y);

  const double REAR_MAX = 0;
  const double REAR_MIN = static_cast<double>(algoParameters::MIN_Y);

  const int NUMBER_OF_BOXES = 8; // Number of containers along the y axis

  const double SENSOR_Z = 2.3; // Known sensor application parameter

  const double SEPARATOR_TRESHHOLD =
      3; // Experiance based algorithm tuning parameter

  const int WINDOW_SIZE = 200; // Sliding window size

  const int WINDOW_STEP_SIZE = 10; // Sliding window step size
};

#endif
