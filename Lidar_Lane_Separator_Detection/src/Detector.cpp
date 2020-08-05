#include "Detector.h"

void Detector::algorithm() {

	// Iterate through all points in the point cloud
	for (int i = 0; i < m_scan.m_data.size(); i++) {

	}

	std::cout << "Total number of pulses: " << m_scan.m_data.size() << std::endl;

	double all = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {
		all += m_scan.m_data[i].m_point.m_zPos;
	}

	std::cout << "Average of all pulse's z component: " << (all / m_scan.m_data.size()) << std::endl;

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
		//std::cout << m_boxes.at(i).m_upperYLimit << "\t" << m_boxes.at(i).m_lowerYLimit << "\t" << m_boxes.at(i).m_upperXLimit << "\t" << m_boxes.at(i).m_lowerXLimit << std::endl;
	}

	std::cout << "Number of boxes (pixels): " << m_boxes.size() << std::endl;

}
