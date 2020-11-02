#include "Material.h"
#include "Math.h"

bool Lambertian::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
    glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - hit.point);

    scattered = ray{ hit.point, direction };
    attenuation = m_albedo;

    return true;
}

bool Metal::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(r.direction), hit.normal);
    scattered = ray{ hit.point, reflected + m_fuzz * randomInUnitSphere() };
    attenuation = m_albedo;

    return (glm::dot(scattered.direction, hit.normal) > 0);
}
