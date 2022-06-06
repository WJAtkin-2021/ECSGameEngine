#pragma once
#include <DirectXMath.h>
#include "Vector3D.h"

enum class LightType : unsigned int
{
	DirectionalLight = 0u,
	PointLight = 1u,
};

struct LightBufferObject
{
	DirectX::XMFLOAT4 m_position;
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT4 m_direction;

	LightType m_type;

	bool m_enabled;
	bool m_padding1;
	bool m_padding2;
	bool m_padding3;
	float m_intensity;
	float m_c1;

	float m_c2;
	float m_padding4;
	float m_padding5;
	float m_padding6;
};

class Light
{
public:
	Light();
	~Light() = default;

	// Getters
	const Vector3D& Position() const { return m_position; }
	const Vector3D& Color() const { return m_color; }
	const Vector3D& Direction() const { return m_direction; }
	LightType Type() const { return m_type; }
	float Intensity() const { return m_intensity; }
	float C1() const { return m_c1; }
	float C2() const { return m_c2; }
	bool Enabled() const { return m_enabled; }

	// Setters
	void SetPosition(const Vector3D& _newPos) { m_position = _newPos; }
	void SetColor(const Vector3D& _newColor) { m_color = _newColor; }
	void SetDirection(const Vector3D& _newDir) { m_direction = _newDir; }
	void SetType(const LightType _newType) { m_type = _newType; }
	void SetIntensity(const float _newIntensity) { m_intensity = _newIntensity; }
	void SetC1(const float _c1) { m_c1 = _c1; }
	void SetC2(const float _c2) { m_c2 = _c2; }
	void Enable() { m_enabled = true; }
	void Disable() { m_enabled = false; }
	void SetEnabledState(const bool _enabled) { m_enabled = _enabled; }

private:

	Vector3D m_position;
	Vector3D m_color;
	Vector3D m_direction;
	LightType m_type;
	float m_intensity;
	float m_c1;
	float m_c2;
	bool m_enabled;
};