#pragma once

#include "Ray.h"

class Geometry
{
public:
	virtual bool Hit(const ray& r, float tMin, float tMax, raycastHit& hit) = 0;

	const glm::vec3& Color() { return m_color; }

protected:
	glm::vec3 m_color{ 0, 0, 0 };
};