#include "Visualization.h"

void Visualization::render(const Scan &scan) {
  glPointSize(2);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.34, -0.11, 0.01);
  glVertex3f(-0.5, 0.7, -0.9);
  glVertex3f(0.8, 0.5, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0.3, 0.3, 0.2);
  glVertex3f(-0.2, 0.7, 0.32);
  glVertex3f(0.28, -0.53, 0.25);
  glVertex3f(0.93, 0.33, 0.52);
  glVertex3f(0.35, 0.17, -0.19);
  glVertex3f(0.48, -0.85, 0.18);
  glEnd();

  glLineWidth(1);
  glBegin(GL_LINES);
  glColor3f(0.0f, 1.0f, 0.0f);

  // Line 1
  glVertex3f(0.9f, -0.3f, -0.7f);
  glVertex3f(-0.5f, -0.4f, -0.1f);

  // Line 2
  glVertex3f(-0.5f, -0.4f, -0.3f);
  glVertex3f(-0.9f, -0.8f, -0.1f);

  glEnd();
}

// Temporary code, TODO: Refactor
void Visualization::transformToArray() {
  for (int i = 0, j = 0; i < m_elements; i += m_dimensions, j++) {
    m_vertices[i] = m_scan.m_data[j].m_point.m_xPos;
    m_vertices[i + 1] = m_scan.m_data[j].m_point.m_yPos;
    m_vertices[i + 2] = m_scan.m_data[j].m_point.m_zPos;
  }
}
