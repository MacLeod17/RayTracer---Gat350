#include "Plane.h"

bool Plane::Hit(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    float denominator = glm::dot(r.direction, m_normal);

    if (denominator == 0) return false;
    if (abs(denominator) < std::numeric_limits<float>::epsilon())
    {
        return false; // direction and plane parallel, no intersection
    }

    float t = glm::dot(m_center - r.origin, m_normal) / denominator;
    if (t < 0) return false;
    if (t > tMin && t < tMax)
    {
        hit.t = t;
        hit.point = r.pointAt(t);
        hit.normal = m_normal;
        hit.material = m_material;
        return true;
    }

    return false;
}
