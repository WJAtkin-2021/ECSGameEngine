#include <Windows.h>
#include <fstream>
#include "Camera.h"
#include "Maths.h"
#include "ResourceManager.h"

using namespace DirectX;

Camera* Camera::m_instance = nullptr;

Camera::Camera()
{
	m_instance = this;

	m_screenWidth = 0;
	m_screenHeight = 0;

	m_viewMatrix = XMMatrixIdentity();
	m_projectionMatrix = XMMatrixIdentity();
}

Camera::Camera(int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;
}

Camera::~Camera() { }

void Camera::SetWindowSize(int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	// Create the rotation matrix using the cameras transform
	float rotX = MathsFunctions::GetRadians(m_transform.Rotation().m_x);
	float rotY = MathsFunctions::GetRadians(m_transform.Rotation().m_y);
	float rotZ = MathsFunctions::GetRadians(m_transform.Rotation().m_z);
	const XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);

	// Create the new at and up vectors
	XMVECTOR m_at = XMVector3TransformCoord(m_defaultViewAngle, rotMat);
	XMVECTOR m_up = XMVector3TransformCoord(m_defaultUpAngle, rotMat);

	// Find the new eye position
	const XMVECTOR m_eye = XMVectorSet(m_transform.Position().m_x, m_transform.Position().m_y, m_transform.Position().m_z, 0.0f);

	// Take the camera position into account
	m_at = m_eye + m_at;

	m_viewMatrix = XMMatrixLookAtLH(m_eye, m_at, m_up);

	m_viewMatrix = XMMatrixTranspose(m_viewMatrix);

	return m_viewMatrix;
}

DirectX::XMMATRIX Camera::GetProjMatrix()
{
	m_projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, static_cast<FLOAT>(m_screenWidth) / static_cast<FLOAT>(m_screenHeight), 0.01f, 100.0f);
	m_projectionMatrix = XMMatrixTranspose(m_projectionMatrix);
	return m_projectionMatrix;
}

void Camera::WriteDataToFile(std::ofstream& _saveFile)
{
	Vector3D pos = m_transform.Position();
	Vector3D rot = m_transform.Rotation();

	_saveFile << "<Camera>\n";
	_saveFile << "<Position> " << pos.m_x << " " << pos.m_y << " " << pos.m_z << " </Position>\n";
	_saveFile << "<Rotation> " << rot.m_x << " " << rot.m_y << " " << rot.m_z << " </Rotation>\n";
	_saveFile << "</Camera>\n";
}

void Camera::ReadDataFromFile(std::ifstream& _openFile)
{
	std::string data = "";
	_openFile >> data;
	_openFile >> data;

	// Position
	Vector3D pos;
	_openFile >> data;
	pos.m_x = std::stof(data);
	_openFile >> data;
	pos.m_y = std::stof(data);
	_openFile >> data;
	pos.m_z = std::stof(data);
	_openFile >> data;
	// Rotation
	Vector3D rot;
	_openFile >> data;
	_openFile >> data;
	rot.m_x = std::stof(data);
	_openFile >> data;
	rot.m_y = std::stof(data);
	_openFile >> data;
	rot.m_z = std::stof(data);

	m_transform.SetPosition(pos);
	m_transform.SetRotation(rot);
}
