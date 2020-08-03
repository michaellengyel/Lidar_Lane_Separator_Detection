#include "Detector.h"

void Detector::algorithm() {

	// Cluster the data into space boxes
	cluster();

	// Sort all datapoints in all slices based on size of x component

	// Left side
	for (int i = 0; i < m_spaceBoxsLeft.size(); i++) {
		std::sort(m_spaceBoxsLeft.at(i).m_xPoints.begin(), m_spaceBoxsLeft.at(i).m_xPoints.end(), std::greater<double>());
	}

	// Right side
	for (int i = 0; i < m_spaceBoxsRight.size(); i++) {
		std::sort(m_spaceBoxsRight.at(i).m_xPoints.begin(), m_spaceBoxsRight.at(i).m_xPoints.end(), std::greater<double>());
	}


	// Call sliding window funcion on space boxes
	// left side
	slidingWindow(m_spaceBoxsLeft);

	// Right side
	slidingWindow(m_spaceBoxsRight);

	
	std::cout << "Number of pulse points: " << m_scan.m_data.size() << std::endl;

	double all = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {
		all += m_scan.m_data[i].m_point.m_zPos;
	}

	std::cout << all/ m_scan.m_data.size() << std::endl;

	// Setting up mock data
	//Point point1(-1.7f, -30.0f, -2.3f);
	//Point point2(-1.7f, 30.0f, -2.3f);

	// Call the segmentMaker to re-wrap the segments to be rendered
	segmentMaker();

}

void Detector::init() {

	// Calculate size of increment
	double range = FRONT_MAX - REAR_MIN;
	double boxYSize = range / NUMBER_OF_BOXES;

	double lowerBound = REAR_MIN; // init lowerBound with min value

	// Create and init a fixed number of SpaceBoxs
	for (int i = 0; i < NUMBER_OF_BOXES; i++) {
		
		SpaceBox spaceBox(lowerBound + boxYSize, lowerBound);

		spaceBox.m_yCoord = lowerBound + (boxYSize / 2);

		m_spaceBoxsLeft.push_back(spaceBox); // Mirror left and right containers
		m_spaceBoxsRight.push_back(spaceBox); // Mirror left and right containers

		lowerBound += boxYSize;
	}

}

void Detector::cluster() {

	double xCurrent = 0;
	double yCurrent = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {

		xCurrent = m_scan.m_data.at(i).m_point.m_xPos;
		yCurrent = m_scan.m_data.at(i).m_point.m_yPos;

		// Sorting of the points into their respective containers
		// if: left side
		if (xCurrent < 0) {
			for (int i = 0; i < m_spaceBoxsLeft.size(); i++) {
				// If the point is in the range of the box at pos i
				if ((yCurrent >= m_spaceBoxsLeft.at(i).m_lowerLimit) && (yCurrent < m_spaceBoxsLeft.at(i).m_upperLimit) ) {
					// Add the points y coord to the relevant container
					m_spaceBoxsLeft.at(i).m_xPoints.push_back(xCurrent);
					break;
				}
			}
		}
		// if: right side
		else if (xCurrent >= 0) {
			for (int i = 0; i < m_spaceBoxsRight.size(); i++) {
				// If the point is in the range of the box at pos i
				if ((yCurrent >= m_spaceBoxsRight.at(i).m_lowerLimit) && (yCurrent < m_spaceBoxsRight.at(i).m_upperLimit)) {
					// Add the points y coord to the relevant container
					m_spaceBoxsRight.at(i).m_xPoints.push_back(xCurrent);
					break;
				}
			}
		}
	
	}


	for (int i = 0; i < m_spaceBoxsLeft.size(); i++) {
		std::cout << "Left side, container: " << i << " is " << m_spaceBoxsLeft.at(i).m_xPoints.size() << std::endl; //LOGGING COMMENT
	}

	for (int i = 0; i < m_spaceBoxsRight.size(); i++) {
		std::cout << "Right side, container: " << i << " is " << m_spaceBoxsRight.at(i).m_xPoints.size() << std::endl; //LOGGING COMMENT
	}


}

void Detector::slidingWindow(std::vector<SpaceBox> &box) {

	for (int k = 0; k < box.size(); k++) {
		// Calculate average of points 
		double average = boxAverage(box.at(k).m_xPoints);

		// Calculate average value of sliding window
		for (int i = 0; i < box.at(k).m_xPoints.size() - WINDOW_SIZE; i+=WINDOW_STEP_SIZE) {

			double windowTotal = 0;

			for (int j = 0; j < WINDOW_SIZE - 1; j++) {
				windowTotal += (box.at(k).m_xPoints.at(i + j) - box.at(k).m_xPoints.at(i + j + 1));
			}

			double windowAverage = windowTotal / WINDOW_SIZE;

			// std::cout << "Window average: " << windowAverage << std::endl; //LOGGING COMMENT

			// If window average times a treshhold value is greater then the box average
			if ((windowAverage * SEPARATOR_TRESHHOLD) < average) {
				box.at(k).m_xCoord = box.at(k).m_xPoints.at(i);
				break;
			}

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

void Detector::segmentMaker() {

	// Left side
	for (int i = 0; i < m_spaceBoxsLeft.size() - 1; i++) {

		Point pointRight1(m_spaceBoxsLeft.at(i).m_xCoord, m_spaceBoxsLeft.at(i).m_yCoord, -SENSOR_Z);
		Point pointRight2(m_spaceBoxsLeft.at(i + 1).m_xCoord, m_spaceBoxsLeft.at(i + 1).m_yCoord, -SENSOR_Z);

		Segment segment(pointRight1, pointRight2);

		m_segments.push_back(segment);
	}

	// Right side
	for (int i = 0; i < m_spaceBoxsRight.size() - 1; i++) {

		Point pointRight1(m_spaceBoxsRight.at(i).m_xCoord, m_spaceBoxsRight.at(i).m_yCoord, -SENSOR_Z);
		Point pointRight2(m_spaceBoxsRight.at(i + 1).m_xCoord, m_spaceBoxsRight.at(i + 1).m_yCoord, -SENSOR_Z);

		Segment segment(pointRight1, pointRight2);

		m_segments.push_back(segment);
	}

}
