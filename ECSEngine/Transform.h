#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "Vector3D.h"

class Transform : public Component
{
public:
	Transform();
	Transform(Entity* _entity, int _compId);
	~Transform();

	// Getters
	Transform* GetThis() override { return this; }
	Vector3D Position() const { return m_position; }
	Vector3D Rotation() const { return m_rotation; }
	Vector3D Scale() const { return m_scale; }
	Vector3D LookVector();
	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMMATRIX GetInvWorldMatrix() { return m_invWorld; }

	// Setters
	// Setters for pos, rot and scale
	void SetPosition(const Vector3D& newPosition) { m_position = newPosition; RecalculateWorldMat(); }
	void SetRotation(const Vector3D& newRotation) { m_rotation = newRotation; RecalculateWorldMat(); }
	void SetScale(const Vector3D& newScale) { m_scale = newScale; RecalculateWorldMat(); }
	// Position component setters
	void SetPosX(const float newX) { m_position.m_x = newX; RecalculateWorldMat(); }
	void SetPosY(const float newY) { m_position.m_y = newY; RecalculateWorldMat(); }
	void SetPosZ(const float newZ) { m_position.m_z = newZ; RecalculateWorldMat(); }
	// Rotation component setters
	void SetRotX(const float newX) { m_rotation.m_x = newX; CheckRotations(); RecalculateWorldMat(); }
	void SetRotY(const float newY) { m_rotation.m_y = newY; CheckRotations(); RecalculateWorldMat(); }
	void SetRotZ(const float newZ) { m_rotation.m_z = newZ; CheckRotations(); RecalculateWorldMat(); }
	// Scale component setters
	void SetScaleX(const float newX) { m_scale.m_x = newX; RecalculateWorldMat(); }
	void SetScaleY(const float newY) { m_scale.m_y = newY; RecalculateWorldMat(); }
	void SetScaleZ(const float newZ) { m_scale.m_z = newZ; RecalculateWorldMat(); }

	// Move functions
	void Move(const Vector3D& moveVec) { m_position += moveVec; }
	void MoveX(const float newX) { m_position.m_x += newX; RecalculateWorldMat(); }
	void MoveY(const float newY) { m_position.m_y += newY; RecalculateWorldMat(); }
	void MoveZ(const float newZ) { m_position.m_z += newZ; RecalculateWorldMat(); }
	void MoveLocalX(const float newX);
	void MoveLocalY(const float newY);
	void MoveLocalZ(const float newZ);

	// Rotate functions
	void RotateX(const float newX) { m_rotation.m_x += newX; CheckRotations(); RecalculateWorldMat(); }
	void RotateY(const float newY) { m_rotation.m_y += newY; CheckRotations(); RecalculateWorldMat(); }
	void RotateZ(const float newZ) { m_rotation.m_z += newZ; CheckRotations(); RecalculateWorldMat(); }

	void WriteDataToFile(std::ofstream& _saveFile) override;
	void ReadDataFromFile(std::ifstream& _openFile) override;

private:
	// Hide the update functions here as they are called on the base
	// class
	void Update() override {}
	void StepPhysics() override {}
	bool DrawImGuiInterface() override;

	// Helper functions
	void InitTransform();
	void RecalculateWorldMat();
	void CheckRotations(); 	// Check that rotations are not overflowing
	void MoveViaLocalAxis(const float _moveAmount, const DirectX::XMVECTOR _moveAxis);
	
	// Pos, rot and scale
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale;

	// World mat
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_invWorld;
};