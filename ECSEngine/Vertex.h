#pragma once
#include "Vector3D.h"

struct Vertex
{
public:
	Vertex();
	Vertex(const Vector3D _pos, const Vector3D _normal, const Vector3D _tangent, const Vector3D _uv);
	Vertex(const float _px, const float _py, const float _pz,
		const float _nx, const float _ny, const float _nz,
		const float _tx, const float _ty, const float _tz,
		const float _u, const float _v);
	~Vertex();

	Vector3D m_position;
	Vector3D m_normal;
	Vector3D m_tangent;
	Vector3D m_uv;
};