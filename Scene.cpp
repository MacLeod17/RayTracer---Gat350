#include "Scene.h"
#include "Geometry.h"
#include "Math.h"

glm::vec3 Scene::Trace(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    bool rayHit = false;

    float tClosest = tMax;

    for (auto object : m_objects)
    {
        if (object->Hit(r, tMin, tClosest, hit))
        {
            rayHit = true;
            tClosest = hit.t;
        }
    }

    if (rayHit)
    {
        glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
        glm::vec3 direction = glm::normalize(target - hit.point);
        ray newRay{ hit.point, direction };
        return { Trace(newRay, tMin, tMax, hit) * 0.5f };
    }
    else
    {
        glm::vec3 direction = glm::normalize(r.direction);
        float t = (direction.y + 1) * 0.5f;
        return glm::lerp(glm::vec3{ 0.5f, 0.7f, 1.0f }, glm::vec3{ 1, 1, 1 }, t);
    }
}

void Scene::Add(Geometry* geometry)
{
    m_objects.push_back(geometry);
}
