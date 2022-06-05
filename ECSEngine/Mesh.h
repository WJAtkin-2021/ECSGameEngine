#pragma once
#include <string>
#include <vector>
#include <memory>
#include "PrimativeTypes.h"
#include "Vertex.h"

// Forward Declarations
class GPUBuffers;
class Mesh
{
public:
	Mesh();
	Mesh(const std::string _filePath);
	Mesh(const PrimitiveTypes _primitiveType);
	~Mesh();

	// Setters
	void SetBuffersForDrawCall();

	// Getters
	int GetNumberOfIndicies();
	PrimitiveTypes GetPrimativeType() { return m_primativeType; }
	std::string GetMeshFilePath() { return m_filePath; }

private:

	// The GPU buffer object, used for handling vertex and index buffers on the GPU
	std::shared_ptr<GPUBuffers> m_GPUBuffers;

	// The meshes file path or primitive type
	std::string m_filePath;
	PrimitiveTypes m_primativeType;

	// Helper functions
	void CreateGPUBuffer();
	void LoadPrimativeMesh(const PrimitiveTypes _primitiveType, std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies);
	void GeneratePrimativeCube(const PrimitiveTypes _primitiveType, std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies);
	void LoadMeshWithAssImp(const std::string _filePath, std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies);
};