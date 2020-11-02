#pragma once

#include "Image.h"
#include "Types.h"
#include "Scene.h"

class Tracer
{
public:
	Tracer(int samples, int depth) : m_samples{ samples }, m_depth{ depth } {}

	void Trace(Image& image, Scene& scene);

private:
	glm::vec3 m_origin{ 0, 0, 5 };
	int m_samples{ 1 };
	int m_depth{ 5 };
};