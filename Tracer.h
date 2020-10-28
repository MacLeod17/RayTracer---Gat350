#pragma once

#include "Image.h"
#include "Types.h"
#include "Scene.h"

class Tracer
{
public:
	Tracer() {}

	void Trace(Image& image, Scene& scene);

private:
	glm::vec3 m_origin{ 0, 0, 5 };
};