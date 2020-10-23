#pragma once

#include "Image.h"
#include "Types.h"

class Tracer
{
public:
	Tracer() {}

	void Trace(Image& image, std::vector<class Geometry*>& scene);

private:
	glm::vec3 m_origin{ 0, 0, 5 };
};