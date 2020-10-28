
#include "Sphere.h"
#include "Tracer.h"

void Tracer::Trace(Image& image, Scene& scene)
{
	float aspectRatio = image.width() / (float)image.height();

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			glm::vec3 p;
			p.x = x / (float)image.width();
			p.y = 1 - (y / (float)image.height());
			p.z = 0;

			glm::vec3 direction = glm::vec3{ glm::vec2{p} * 2.0f - 1.0f, -1 };
			direction.y /= aspectRatio;
			direction = glm::normalize(direction);

			ray r{ m_origin, direction };
			raycastHit hit;

			if (scene.Trace(r, 0, FLT_MAX, hit))
			{
				image.SetPoint({ x, y }, hit.normal);
			}
		}
	}
}
