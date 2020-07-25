#include "Detector.h"

void Detector::algorithm() {
	std::cout << m_scan.m_data.size() << std::endl;

	double all = 0;

	for (int i = 0; i < m_scan.m_data.size(); i++) {
		all += m_scan.m_data[i].m_point.m_zPos;
	}

	std::cout << all/ m_scan.m_data.size() << std::endl;

}