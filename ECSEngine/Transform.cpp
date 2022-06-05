#include "Transform.h"
#include "Maths.h"
#include "StringHelper.h"

Transform::Transform()
{
	InitTransform();
}

Transform::Transform(Entity* _entity, int _compId) : Component(m_entity, _compId)
{
	InitTransform();
}

void Transform::InitTransform()
{
	// Create an initial world matrix
	m_world = DirectX::XMMatrixIdentity();

	// Set the scale
	m_scale = Vector3D(1.0f, 1.0f, 1.0f);
}

Transform::~Transform() { }

Vector3D Transform::LookVector()
{
	// Create a rotation matrix
	float rotX = MathsFunctions::GetRadians(m_rotation.m_x);
	float rotY = MathsFunctions::GetRadians(m_rotation.m_y);
	float rotZ = MathsFunctions::GetRadians(m_rotation.m_z);
	const DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);

	// Create the look vector using the rot matrix
	const DirectX::XMVECTOR defaultViewAngle = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR lookVectorDx = XMVector3TransformCoord(defaultViewAngle, rotMat);
	return Vector3D(lookVectorDx.m128_f32[0], lookVectorDx.m128_f32[1], lookVectorDx.m128_f32[2]);
}

DirectX::XMMATRIX Transform::GetWorldMatrix()
{
	return m_world;
}

void Transform::RecalculateWorldMat()
{
	// Scale
	m_world = DirectX::XMMatrixIdentity();
	m_world *= DirectX::XMMatrixScaling(m_scale.m_x, m_scale.m_y, m_scale.m_z);

	// Rot
	m_world *= DirectX::XMMatrixRotationX(MathsFunctions::GetRadians(m_rotation.m_x));
	m_world *= DirectX::XMMatrixRotationY(MathsFunctions::GetRadians(m_rotation.m_y));
	m_world *= DirectX::XMMatrixRotationZ(MathsFunctions::GetRadians(m_rotation.m_z));

	// Pos
	m_world *= DirectX::XMMatrixTranslation(m_position.m_x, m_position.m_y, m_position.m_z);

	// Transpose
	m_world = DirectX::XMMatrixTranspose(m_world);
}

void Transform::CheckRotations()
{
	// X
	while (m_rotation.m_x >= 360.0f)
	{
		m_rotation.m_x -= 360.0f;
	}
	while (m_rotation.m_x <= -360.0f)
	{
		m_rotation.m_x += 360.0f;
	}
	// Y
	while (m_rotation.m_y >= 360.0f)
	{
		m_rotation.m_y -= 360.0f;
	}
	while (m_rotation.m_y <= -360.0f)
	{
		m_rotation.m_y += 360.0f;
	}
	// Z
	while (m_rotation.m_z >= 360.0f)
	{
		m_rotation.m_z -= 360.0f;
	}
	while (m_rotation.m_z <= -360.0f)
	{
		m_rotation.m_z += 360.0f;
	}
}

void Transform::MoveLocalX(const float newX)
{
	const DirectX::XMVECTOR moveAxis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	MoveViaLocalAxis(newX, moveAxis);
}

void Transform::MoveLocalY(const float newY)
{
	const DirectX::XMVECTOR moveAxis = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	MoveViaLocalAxis(newY, moveAxis);
}

void Transform::MoveLocalZ(const float newZ)
{
	const DirectX::XMVECTOR moveAxis = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	MoveViaLocalAxis(newZ, moveAxis);
}

void Transform::MoveViaLocalAxis(const float _moveAmount, const DirectX::XMVECTOR _moveAxis)
{
	// Create a rotation matrix
	float rotX = MathsFunctions::GetRadians(m_rotation.m_x);
	float rotY = MathsFunctions::GetRadians(m_rotation.m_y);
	float rotZ = MathsFunctions::GetRadians(m_rotation.m_z);
	const DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);

	// Create the look vector using the rot matrix
	const DirectX::XMVECTOR lookVectorDx = XMVector3TransformCoord(_moveAxis, rotMat);
	Vector3D lookVector = Vector3D(lookVectorDx.m128_f32[0], lookVectorDx.m128_f32[1], lookVectorDx.m128_f32[2]);

	// Adjust this with the amount we need to move
	lookVector = lookVector.multiplyByScalar(_moveAmount);
	m_position += lookVector;

	RecalculateWorldMat();
}

bool Transform::DrawImGuiInterface()
{
	std::string headerTitle = std::to_string(GetCompId()) + ": Transform";
	if (ImGui::CollapsingHeader(headerTitle.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		using namespace StringHelper;
	
		// Position
		float vec3Pos[3] = { m_position.m_x, m_position.m_y, m_position.m_z };
		ImGui::Text("Position:");
		ImGui::SameLine(75.0f);
		ImGui::DragFloat3(GenerateImGuiHash(GetCompId(), 0).c_str(), vec3Pos, 0.01f, -1000.0f, 1000.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_position = Vector3D(vec3Pos[0], vec3Pos[1], vec3Pos[2]);
		// Rotation
		float vec3Rot[3] = { m_rotation.m_x, m_rotation.m_y, m_rotation.m_z };
		ImGui::Text("Rotation:");
		ImGui::SameLine(75.0f);
		ImGui::DragFloat3(GenerateImGuiHash(GetCompId(), 1).c_str(), vec3Rot, 0.01f, -1000.0f, 1000.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_rotation = Vector3D(vec3Rot[0], vec3Rot[1], vec3Rot[2]);
		// Scale
		float vec3Scale[3] = { m_scale.m_x, m_scale.m_y, m_scale.m_z };
		ImGui::Text("Scale:");
		ImGui::SameLine(75.0f);
		ImGui::DragFloat3(GenerateImGuiHash(GetCompId(), 2).c_str(), vec3Scale, 0.01f, -1000.0f, 1000.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_scale = Vector3D(vec3Scale[0], vec3Scale[1], vec3Scale[2]);
	
		// Recalc world matrix as we may be editing the transform
		RecalculateWorldMat();
	
		// Check to make sure rotations didn't overflow too
		CheckRotations();
	}

	return true;
}