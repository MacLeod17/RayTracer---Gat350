#pragma once

#include "Geometry.h"
#include "Types.h"

class Sphere : public Geometry
{
public:
	Sphere() {}
	Sphere(const glm::vec3& center, float radius, const glm::vec3& color) : 
		m_center(center), m_radius(radius), m_color(color) {}

	bool Hit(const ray& r) override;

	glm::vec3 m_color{ 0, 0, 0 };
private:
	glm::vec3 m_center{ 0, 0, 0 };
	float m_radius = 0;
};