//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef VISUALIZATON
#define VISUALIZATON
#include "Scan.h"
#include "Enumerations.h"

#include <GLFW/glfw3.h>

//============================================================================================================
// Class Documentation Placeholder
// TODO: Switch to Doxygen format(///)
//============================================================================================================

class Visualization {
public:

	Visualization(const Scan& scan) : m_scan(scan) {

	}

	~Visualization() {

	}

	void render(const Scan& scan);

	void transformToArray();

private:

	const Scan& m_scan;

public:

	const static int m_points = g_points;
	const static int m_dimensions = 3;

	const static int m_elements = m_points * m_dimensions;

	float m_vertices[m_elements];
};

#endif