#include "Vertex.h"

Vertex::Vertex() { }

Vertex::Vertex(const Vector3D _pos, const Vector3D _normal, const Vector3D _tangent, const Vector3D _uv)
{
	m_position = _pos;
	m_normal = _normal;
	m_tangent = _tangent;
	m_uv = _uv;
}

Vertex::Vertex(const float _px, const float _py, const float _pz, const float _nx, const float _ny, const float _nz,
	const float _tx, const float _ty, const float _tz, const float _u, const float _v)
{
	m_position = Vector3D(_px, _py, _pz);
	m_normal = Vector3D(_nx, _ny, _nz);
	m_tangent = Vector3D(_tx, _ty, _tz);
	m_uv = Vector3D(_u, _v, 0.0f);
}

Vertex::~Vertex() { }