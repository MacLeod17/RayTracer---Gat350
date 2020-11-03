#pragma once

#include "Camera.h"
#include "Image.h"
#include "Scene.h"
#include "Types.h"

class Tracer
{
public:
	Tracer(int samples, int depth) : m_samples{ samples }, m_depth{ depth } {}

	void Trace(Image& image, Scene& scene, Camera& camera);

private:
	glm::vec3 m_origin{ 0, 0, 5 };
	int m_samples{ 1 };
	int m_depth{ 5 };
};