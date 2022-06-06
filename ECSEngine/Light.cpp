#include "Light.h"

Light::Light()
{
	// Set default variables
	m_position = Vector3D();
	m_color = Vector3D(1.0f, 0.929f, 0.612f);
	m_direction = Vector3D(0.5f, 0.5f, 0.0f);
	m_type = LightType::PointLight;
	m_intensity = 1.0f;
	m_enabled = true;
	m_c1 = 1.6f;
	m_c2 = 0.8f;
}