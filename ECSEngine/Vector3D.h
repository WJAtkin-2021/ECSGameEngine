#pragma once
#ifdef BUILD_DX_11
#include <DirectXMath.h>
#endif // BUILD_DX_11

class Vector3D
{
public:

	Vector3D();
	Vector3D(const float _xyz);
	Vector3D(const float _x, const float _y, const float _z);
	~Vector3D();

	Vector3D operator + (const Vector3D& _rhs);
	Vector3D operator - (const Vector3D& _rhs);
	Vector3D operator * (const Vector3D& _rhs);
	Vector3D operator / (const Vector3D& _rhs);
	Vector3D operator - () const;

	Vector3D& operator += (const Vector3D& _rhs);

	// Scale the whole vector by a scalar
	Vector3D multiplyByScalar(const float& _s) const { return { m_x * _s, m_y * _s, m_z * _s }; }

	// Squared length of vector. When comparing length, it is generally faster to compare the squared length to avoid the square root calculation
	float lengthSqr() const { return (m_x * m_x + m_y * m_y + m_z * m_z); }

	// Length of vector. This returns the length (magnitude) of the vector
	float length() const;

	// Normalise a vector. The operation L.Normalise(R) replaces L with the normalised (unit length) version of R. It is equivalent to L=R.Normalise() but with less overhead, since a temporary object	is not returned.
	const Vector3D& normalize(const Vector3D& v);
	const Vector3D& normalize() { return normalize(*this); }

#ifdef BUILD_DX_11

	// Returns a XMFLOAT4 of this vector
	const DirectX::XMFLOAT4 GetXMFLOAT4() const { return DirectX::XMFLOAT4(m_x, m_y, m_z, 1.0f); }

#endif // BUILD_DX_11

	float m_x, m_y, m_z;

private:

	static constexpr float m_epsilon = 1.0e-8f;
};