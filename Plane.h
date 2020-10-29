#pragma once

#include "Geometry.h"
#include "Types.h"

class Plane : public Geometry
{
public:
	Plane(const glm::vec3& center, const glm::vec3& normal, const glm::vec3& color) :
		m_center{ center },
		m_normal{ normal }
	{
		m_color = color;
	}

	bool Hit(const ray& r, float tMin, float tMax, raycastHit& hit) override;

private:
	glm::vec3 m_center{ 0, 0, 0 };
	glm::vec3 m_normal{ 0, 0, 0 };
};
