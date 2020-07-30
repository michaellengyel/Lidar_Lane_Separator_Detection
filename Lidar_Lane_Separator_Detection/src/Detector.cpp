#include "Detector.h"

void Detector::algorithm() {

	// Cluster the data into space boxes
	cluster();

	// Sort all datapoints in all slices based on size of x component

	// Right Side
	std::sort(m_xFrontRight.begin(), m_xFrontRight.end(), std::greater<double>());
	std::sort(m_xRearRight.begin(), m_xRearRight.end(), std::greater<double>());

	// Left Side
	std::sort(m_xFrontLeft.begin(), m_xFrontLeft.end(), std::greater<double>());
	std::sort(m_xRearLeft.begin(), m_xRearLeft.end(), std::greater<double>());

	// Call sliding window funcion on space boxes

	// Sliding window functions (Right side)
	slidingWindow(m_xFrontRight, m_frontRight);
	slidingWindow(m_xRearRight, m_RearRight);

	// Sliding window functions (Left side)
	slidingWindow(m_xFrontLeft, m_frontLeft);
	slidingWindow(m_xRearLeft, m_RearLeft);
	
	std::cout << "Number of pulse points: " << m_scan.m_data.size() << std::endl;

	double all = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {
		all += m_scan.m_data[i].m_point.m_zPos;
	}

	std::cout << all/ m_scan.m_data.size() << std::endl;

	// Setting up mock data
	//Point point1(-1.7f, -30.0f, -2.3f);
	//Point point2(-1.7f, 30.0f, -2.3f);

	// Segment (Right Side)
	Point pointRight1(m_frontRight, REAR_MIN, -SENSOR_Z);
	Point pointRight2(m_RearRight, FRONT_MAX, -SENSOR_Z);

	Segment segmentRight(pointRight1, pointRight2);
	m_segmentRight = segmentRight;

	// Segment (Left Side)
	Point pointLeft1(m_frontLeft, REAR_MIN, -SENSOR_Z);
	Point pointLeft2(m_RearLeft, FRONT_MAX, -SENSOR_Z);

	Segment segment(pointLeft1, pointLeft2);
	m_segmentLeft = segment;

}

void Detector::cluster() {

	double xCurrent = 0;
	double yCurrent = 0;

	bool isFrontRight = false;
	bool isRearRight = false;

	bool isFrontLeft = false;
	bool isRearLeft = false;

	for (int i = 0; i < m_scan.m_data.size(); i++) {

		xCurrent = m_scan.m_data.at(i).m_point.m_xPos;
		yCurrent = m_scan.m_data.at(i).m_point.m_yPos;

		isFrontRight = (((yCurrent >= FRONT_MIN) && (yCurrent <= FRONT_MAX)) && (xCurrent >= 0));
		isRearRight = (((yCurrent < REAR_MAX) && (yCurrent >= REAR_MIN)) && (xCurrent >= 0));

		isFrontLeft = (((yCurrent >= FRONT_MIN) && (yCurrent <= FRONT_MAX)) && (xCurrent < 0));
		isRearLeft = (((yCurrent < REAR_MAX) && (yCurrent >= REAR_MIN)) && (xCurrent < 0));

		if (isFrontRight) {
			m_xFrontRight.push_back(xCurrent);
		}
		else if (isRearRight) {
			m_xRearRight.push_back(xCurrent);
		}
		else if (isFrontLeft) {
			m_xFrontLeft.push_back(xCurrent);
		}
		else if (isRearLeft) {
			m_xRearLeft.push_back(xCurrent);
		}
	}

	// std::cout << "m_xFrontRight" << m_xFrontRight.size() << std::endl; //LOGGING COMMENT
	// std::cout << "m_xRearRight" << m_xRearRight.size() << std::endl; //LOGGING COMMENT
	// std::cout << "m_xFrontLeft" << m_xFrontLeft.size() << std::endl; //LOGGING COMMENT
	// std::cout << "m_xRearLeft" << m_xRearLeft.size() << std::endl; //LOGGING COMMENT
}

void Detector::slidingWindow(std::vector<double> &box, double& result) {

	// Calculate average of points 
	double average = boxAverage(box);

	// Calculate average value of sliding window
	for (int i = 0; i < box.size() - WINDOW_SIZE; i++) {

		double windowTotal = 0;

		for (int j = 0; j < WINDOW_SIZE - 1; j++) {
			windowTotal += (box.at(i + j) - box.at(i + j + 1));
		}

		double windowAverage = windowTotal / WINDOW_SIZE;

		// std::cout << "Window average: " << windowAverage << std::endl; //LOGGING COMMENT

		// If window average times a treshhold value is greater then the box average
		if ((windowAverage * SEPARATOR_TRESHHOLD) < average) {
			result = box.at(i);
			return;
		}

	}
}

double Detector::boxAverage(std::vector<double> &box) {

	// Calculate average of points 
	double average = 0;
	double total = 0;

	for (int i = 0; i < box.size() - 1; i++) {
		total += (box.at(i) - box.at(i + 1));
	}

	average = total / box.size();
	// std::cout << "Box average: " << average << std::endl; //LOGGING COMMENT

	return average = total / box.size();
}
