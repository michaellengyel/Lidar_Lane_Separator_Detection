#include "Detector.h"

void Detector::algorithm() {

	// Cluster the data into space boxes
	cluster();

	// Sort all datapoints in all slices based on size of x component
	std::sort(m_xFrontRight.begin(), m_xFrontRight.end(), std::greater<double>());
	std::sort(m_xRearRight.begin(), m_xRearRight.end(), std::greater<double>());

	std::sort(m_xFrontLeft.begin(), m_xFrontLeft.end(), std::greater<double>());
	std::sort(m_xRearLeft.begin(), m_xRearLeft.end(), std::greater<double>());

	// Test print
	/*
	std::cout.precision(17);
	
	for (int i = 100; i < 1100; i++) {
		//std::cout << (m_xFrontRight.at(i) -m_xFrontRight.at(i + 1)) << std::endl;
		std::cout << m_xFrontLeft.at(i) << std::endl;
	}
	*/

	// Sliding window functions
	slidingWindow_1();
	slidingWindow_2();
	
	std::cout << "Number of pulse points: " << m_scan.m_data.size() << std::endl;

	double all = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {
		all += m_scan.m_data[i].m_point.m_zPos;
	}

	std::cout << all/ m_scan.m_data.size() << std::endl;

	// Setting up mock data
	//Point point1(-1.7f, -30.0f, -2.3f);
	//Point point2(-1.7f, 30.0f, -2.3f);

	Point point1(m_frontLeft, -30.0f, -SENSOR_Z);
	Point point2(m_RearLeft, 30.0f, -SENSOR_Z);

	Segment segment(point1, point2);
	m_segment = segment;

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

	std::cout << "m_xFrontRight" << m_xFrontRight.size() << std::endl;
	std::cout << "m_xRearRight" << m_xRearRight.size() << std::endl;
	std::cout << "m_xFrontLeft" << m_xFrontLeft.size() << std::endl;
	std::cout << "m_xRearLeft" << m_xRearLeft.size() << std::endl;
}

void Detector::slidingWindow_1() {

	// Calculate average of points 
	double average = 0;
	double total = 0;

	for (int i = 0; i < m_xFrontLeft.size() - 1; i++) {
		total += (m_xFrontLeft.at(i) - m_xFrontLeft.at(i + 1));
	}

	average = total / m_xFrontLeft.size();
	std::cout << "Average: " << average << std::endl;

	// Sliding window
	const int WINDOW_SIZE = 1000;


	// Pooling ALGO #1
	for (int i = 0; i < m_xFrontLeft.size() - WINDOW_SIZE; i++) {
		double windowTotal = 0;
		for (int j = 0; j < WINDOW_SIZE - 1; j++) {
			windowTotal += (m_xFrontLeft.at(i + j) - m_xFrontLeft.at(i + j + 1));
		}
		double windowAverage = windowTotal / WINDOW_SIZE;
		//std::cout << "windowAverage: " << windowAverage << std::endl;
		if ((windowAverage * 4) < average) {
			std::cout << "PING" << std::endl;
			std::cout << m_xFrontLeft.at(i) << std::endl;
			m_frontLeft = m_xFrontLeft.at(i);
			return;
		}

	}
}

void Detector::slidingWindow_2() {

	// Calculate average of points 
	double average = 0;
	double total = 0;

	for (int i = 0; i < m_xRearLeft.size() - 1; i++) {
		total += (m_xRearLeft.at(i) - m_xRearLeft.at(i + 1));
	}

	average = total / m_xRearLeft.size();
	std::cout << "Average: " << average << std::endl;

	// Sliding window
	const int WINDOW_SIZE = 1000;


	// Pooling ALGO #1
	for (int i = 0; i < m_xRearLeft.size() - WINDOW_SIZE; i++) {
		double windowTotal = 0;
		for (int j = 0; j < WINDOW_SIZE - 1; j++) {
			windowTotal += (m_xRearLeft.at(i + j) - m_xRearLeft.at(i + j + 1));
		}
		double windowAverage = windowTotal / WINDOW_SIZE;
		//std::cout << "windowAverage: " << windowAverage << std::endl;
		if ((windowAverage * 4) < average) {
			std::cout << "PING" << std::endl;
			std::cout << m_xRearLeft.at(i) << std::endl;
			m_RearLeft = m_xFrontLeft.at(i);
			return;
		}

	}
}