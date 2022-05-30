#include <cmath>
#include "Vector3D.h"

Vector3D::Vector3D()
{
	m_x = m_y = m_z = 0.0f;
}

Vector3D::Vector3D(float _xyz)
{
	m_x = m_y = m_z = _xyz;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
}

Vector3D::~Vector3D()
{

}

Vector3D Vector3D::operator + (const Vector3D& _rhs)
{
	Vector3D result;
	result.m_x = this->m_x + _rhs.m_x;
	result.m_y = this->m_y + _rhs.m_y;
	result.m_z = this->m_z + _rhs.m_z;
	return result;
}

Vector3D Vector3D::operator - (const Vector3D& _rhs)
{
	Vector3D result;
	result.m_x = this->m_x - _rhs.m_x;
	result.m_y = this->m_y - _rhs.m_y;
	result.m_z = this->m_z - _rhs.m_z;
	return result;
}

Vector3D Vector3D::operator * (const Vector3D& _rhs)
{
	Vector3D result;
	result.m_x = this->m_x * _rhs.m_x;
	result.m_y = this->m_y * _rhs.m_y;
	result.m_z = this->m_z * _rhs.m_z;
	return result;
}

Vector3D Vector3D::operator / (const Vector3D& _rhs)
{
	Vector3D result;
	result.m_x = this->m_x / _rhs.m_x;
	result.m_y = this->m_y / _rhs.m_y;
	result.m_z = this->m_z / _rhs.m_z;
	return result;
}

Vector3D& Vector3D::operator += (const Vector3D& _rhs)
{
	this->m_x += _rhs.m_x;
	this->m_y += _rhs.m_y;
	this->m_z += _rhs.m_z;
	return *this;
}

Vector3D Vector3D::operator - () const
{
	Vector3D out;
	out.m_x = -m_x;
	out.m_y = -m_y;
	out.m_z = -m_z;
	return out;
}


float Vector3D::length() const {
	return sqrt(lengthSqr());
}

const Vector3D& Vector3D::normalize(const Vector3D& v) {
	const auto length = v.length();
	if (fabs(length) > m_epsilon) {
		const auto rep = 1.0f / length;
		return *this = { v.m_x * rep, v.m_y * rep, v.m_z * rep };
	}
	return *this;
}