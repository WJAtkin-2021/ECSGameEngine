#pragma once
#include "Transform.h"

class Camera
{
public:
	Camera();
	Camera(int _screenWidth, int _screenHeight);
	~Camera();

	void SetWindowSize(int _screenWidth, int _screenHeight);
	Transform& GetTransform() { return m_transform; }
	static Camera* GetCamera() { return m_instance; }

	DirectX::XMMATRIX GetViewMatrix();
	DirectX::XMMATRIX GetProjMatrix();

	void WriteDataToFile(std::ofstream& _saveFile);
	void ReadDataFromFile(std::ifstream& _openFile);

private:

	static Camera* m_instance;

	// We can reuse the transform component for the camera
	// even though in this build of the engine the camera
	// is not a game object
	Transform m_transform;

	int m_screenWidth;
	int m_screenHeight;

	// Camera variables
	const DirectX::XMVECTOR m_defaultViewAngle = { 0.0f, 0.0f, 1.0f, 0.0f };
	const DirectX::XMVECTOR m_defaultUpAngle = { 0.0f, 1.0f, 0.0f, 0.0f };

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;
};