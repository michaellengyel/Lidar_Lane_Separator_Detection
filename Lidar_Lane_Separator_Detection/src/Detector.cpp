#include "Detector.h"

void Detector::algorithm() {

  gridMaker();
  gridWeightSetter();
  gridFilter();
  hough();

  // Iterate through all points in the point cloud
  for (int i = 0; i < m_scan.m_data.size(); i++) {
  }

  std::cout << "Total number of pulses: " << m_scan.m_data.size() << std::endl;

  double all = 0;

  for (int i = 0; i < m_scan.m_data.size(); i++) {
    all += m_scan.m_data[i].m_point.m_zPos;
  }

  std::cout << "Average of all pulse's z component: "
            << (all / m_scan.m_data.size()) << std::endl;

  // Setting up mock data
  Point point1(-1.7f, -30.0f, -2.3f);
  Point point2(-1.7f, 27.0f, -2.3f);
  Segment segment1(point1, point2);

  Point point3(-14.7f, -3.0f, -2.3f);
  Point point4(-6.7f, 3.0f, -12.3f);
  Segment segment2(point3, point4);

  Point point5(4.7f, -24.0f, 3.3f);
  Point point6(9.7f, 10.0f, -8.3f);
  Segment segment3(point5, point6);

  Point point7(23.7f, -6.0f, 21.3f);
  Point point8(11.7f, 3.0f, -11.3f);
  Segment segment4(point7, point8);

  m_segments.push_back(segment1);
  m_segments.push_back(segment2);
  m_segments.push_back(segment3);
  m_segments.push_back(segment4);
}

void Detector::gridMaker() {

  double yIncrement = DELTA_Y / NUMBER_OF_BOXES;
  double xIncrement = DELTA_X / NUMBER_OF_BOXES;

  double upperYLimit = MIN_Y + yIncrement;
  double lowerYLimit = MIN_Y;
  double upperXLimit = MIN_X + xIncrement;
  double lowerXLimit = MIN_X;

  for (int i = 0; i < NUMBER_OF_BOXES; i++) {
    for (int j = 0; j < NUMBER_OF_BOXES; j++) {
      GridBox gridBox(upperYLimit, lowerYLimit, upperXLimit, lowerXLimit);
      m_boxes.push_back(gridBox);

      upperXLimit += xIncrement;
      lowerXLimit += xIncrement;
    }

    upperXLimit = MIN_X + xIncrement;
    lowerXLimit = MIN_X;

    upperYLimit += yIncrement;
    lowerYLimit += yIncrement;
  }

  for (int i = 0; i < m_boxes.size(); i++) {
    // std::cout << m_boxes.at(i).m_upperYLimit << "\t" <<
    // m_boxes.at(i).m_lowerYLimit << "\t" << m_boxes.at(i).m_upperXLimit <<
    // "\t"
    // << m_boxes.at(i).m_lowerXLimit << std::endl; // DEBUGGING COOMMENT
  }

  std::cout << "Number of boxes (pixels): " << m_boxes.size() << std::endl;
}

void Detector::gridWeightSetter() {

  double xCurrent = 0;
  double yCurrent = 0;

  for (int i = 0; i < m_scan.m_data.size(); i++) {

    xCurrent = m_scan.m_data.at(i).m_point.m_xPos;
    yCurrent = m_scan.m_data.at(i).m_point.m_yPos;

    for (int j = 0; j < m_boxes.size(); j++) {

      bool inRangeY = ((m_boxes.at(j).m_lowerYLimit <= yCurrent) &&
                       (m_boxes.at(j).m_upperYLimit > yCurrent));
      bool inRangeX = ((m_boxes.at(j).m_lowerXLimit <= xCurrent) &&
                       (m_boxes.at(j).m_upperXLimit > xCurrent));

      if (inRangeY && inRangeX) {
        m_boxes.at(j).m_weight++;
      }
    }
  }

  for (int j = 0; j < m_boxes.size(); j++) {
    // std::cout << m_boxes.at(j).m_weight << std::endl; // DEBUGGING COMMENT
  }
}

void Detector::gridFilter() {

  bool filter = false;

  for (int i = 0; i < m_boxes.size() - 1; i++) {

    filter = (m_boxes.at(i).m_weight < FILTER_TRESHOLD);

    if (filter) {
      m_boxes.erase(m_boxes.begin() + i);
      i--;
    } else {
      // Do nothing
    }
  }

  m_boxes.shrink_to_fit();

  std::cout << "Number of boxes (pixels) filtered: " << m_boxes.capacity()
            << std::endl;
}

void Detector::hough() {

  // Start Dirty Hack TODO: Refactor

  std::vector<int> accumulatorTable(THETA_RESOLUTION * RHO_RESOLUTION);

  // End Start Dirty Hack TODO: Refactor

  double xCoord = 0;
  double yCoord = 0;

  for (int i = 0; i < m_boxes.size() - 1; i++) {

    // TODO: Implement hough for unfiltered points

    for (int theta = 0; theta < THETA_RESOLUTION - 1; theta++) {

      xCoord = m_boxes.at(i).m_xCoord;
      yCoord = m_boxes.at(i).m_yCoord;

      // using form RHO = Xi*cos(THETA) + Yi*sin(THETA)
      double rho =
          xCoord * cos(theta * PI / 180) + yCoord * sin(theta * PI / 180);

      int normalizedRho = accumulatorNormalizer(rho);

      accumulatorTable.at(dimensionConverter(
          normalizedRho, theta, RHO_RESOLUTION, THETA_RESOLUTION)) += 1;

      // std::cout.precision(17); // DEBUGGING COMMENT
      // std::cout << theta << "," << normalizedRho << std::endl; // DEBUGGING
      // COMMENT
    }
  }

  // filterTopIntersects(accumulatorTable);
}

int Detector::accumulatorNormalizer(double rho) {

  // Offset rho to make sure it's positive
  double offset = SQRTWO * MAX_Y;
  rho = rho + offset;

  double norm = 1 / rho;
  double scaledNorm = norm * RHO_RESOLUTION;

  return static_cast<int>(scaledNorm);
}

int Detector::dimensionConverter(int i, int j, int iSize, int jSize) {

  return ((i * jSize) + j);
}

void Detector::filterTopIntersects(std::vector<int> &accumulatorTable) {

  for (int i = 0; i < accumulatorTable.size(); i++) {

    if (accumulatorTable.at(i) > HOUGH_TRESHOLD) {
      std::cout << "ping" << std::endl;
    }
  }
}
