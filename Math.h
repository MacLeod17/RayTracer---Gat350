#pragma once

#include "Types.h"
#include <stdlib.h>
#include <algorithm>

inline float random01()
{
	return rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
	if (min > max) std::swap(min, max);

	return min + ((max - min) * random01());
}

inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 p;

	do
	{
		p = glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) };
	} while (glm::length2(p) >= 1);

	return p;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
	glm::vec3 r = v - (2 * glm::dot(v, n) * n);

	return r;
}