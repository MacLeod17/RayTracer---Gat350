#include "Scene.h"
#include "Geometry.h"

bool Scene::Trace(const ray& r, float tMin, float tMax, raycastHit& hit)
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

    return rayHit;
}

void Scene::Add(Geometry* geometry)
{
    m_objects.push_back(geometry);
}
