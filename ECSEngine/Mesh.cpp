#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include <stdexcept>
#include "Mesh.h"
#include "GPUBuffers.h"

Mesh::Mesh()
{
	m_filePath = "";
	m_primativeType = PrimitiveTypes::INVALID;
}

Mesh::Mesh(const std::string _filePath)
{
	m_filePath = _filePath;
	m_primativeType = PrimitiveTypes::INVALID;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;

	// Load the file with assImp and check if it is valid
	LoadMeshWithAssImp(_filePath, vertices, indicies);

	// Tell the GPUBuffer to load the buffers onto the GPU
	CreateGPUBuffer();
	m_GPUBuffers->SetVertexVector(vertices);
	m_GPUBuffers->SetIndexVector(indicies);
	m_GPUBuffers->GenerateBuffers();
}

Mesh::Mesh(const PrimitiveTypes _primitiveType)
{
	m_filePath = "";
	m_primativeType = _primitiveType;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;

	LoadPrimativeMesh(_primitiveType, vertices, indicies);

	// Tell the GPUBuffer to load the buffers onto the GPU
	CreateGPUBuffer();
	m_GPUBuffers->SetVertexVector(vertices);
	m_GPUBuffers->SetIndexVector(indicies);
	m_GPUBuffers->GenerateBuffers();
}

Mesh::~Mesh() {}

void Mesh::CreateGPUBuffer()
{
	m_GPUBuffers = GPUBuffers::FactoryCreateGPUBuffers();
}

void Mesh::LoadPrimativeMesh(const PrimitiveTypes _primitiveType, std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies)
{
	switch (_primitiveType)
	{
	case PrimitiveTypes::Cube:
		GeneratePrimativeCube(_verticies, _indicies);
		break;
	case PrimitiveTypes::Sphere:
		GeneratePrimativeSphere(_verticies, _indicies);
		break;
	default:
		throw std::invalid_argument("Primitive type unhanded");
	}
}

void Mesh::SetBuffersForDrawCall()
{
	m_GPUBuffers->SetBuffersForDrawCall();
}

int Mesh::GetNumberOfIndicies()
{
	return m_GPUBuffers->GetNumberOfIndicies();
}

void Mesh::GeneratePrimativeCube(std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies)
{
	Vertex vertices[24];

	const float width = 0.5f;

	// front face
	_verticies.push_back(Vertex(-width, -width, -width, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(-width, +width, -width, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(+width, +width, -width, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	_verticies.push_back(Vertex(+width, -width, -width, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// back face
	_verticies.push_back(Vertex(-width, -width, +width, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	_verticies.push_back(Vertex(+width, -width, +width, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(+width, +width, +width, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(-width, +width, +width, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));

	// top face
	_verticies.push_back(Vertex(-width, +width, -width, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(-width, +width, +width, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(+width, +width, +width, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
	_verticies.push_back(Vertex(+width, +width, -width, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));

	// bottom face
	_verticies.push_back(Vertex(-width, -width, -width, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	_verticies.push_back(Vertex(+width, -width, -width, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(+width, -width, +width, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(-width, -width, +width, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));

	// left face
	_verticies.push_back(Vertex(-width, -width, +width, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(-width, +width, +width, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(-width, +width, -width, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_verticies.push_back(Vertex(-width, -width, -width, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	// right face
	_verticies.push_back(Vertex(+width, -width, -width, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	_verticies.push_back(Vertex(+width, +width, -width, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
	_verticies.push_back(Vertex(+width, +width, +width, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
	_verticies.push_back(Vertex(+width, -width, +width, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));

	// Create the index list
	_indicies.push_back(0u); _indicies.push_back(1u); _indicies.push_back(2u); // Triangle 1 -z
	_indicies.push_back(0u); _indicies.push_back(2u); _indicies.push_back(3u); // Triangle 2

	_indicies.push_back(4u); _indicies.push_back(5u); _indicies.push_back(6u); // Triangle 3 +z
	_indicies.push_back(4u); _indicies.push_back(6u); _indicies.push_back(7u); // Triangle 4

	_indicies.push_back(8u); _indicies.push_back(9u); _indicies.push_back(10u); // Triangle 5 +y
	_indicies.push_back(8u); _indicies.push_back(10u); _indicies.push_back(11u); // Triangle 6

	_indicies.push_back(12u); _indicies.push_back(13u); _indicies.push_back(14u); // Triangle 7 -y
	_indicies.push_back(12u); _indicies.push_back(14u); _indicies.push_back(15u); // Triangle 8

	_indicies.push_back(16u); _indicies.push_back(17u); _indicies.push_back(18u); // Triangle 9 -x
	_indicies.push_back(16u); _indicies.push_back(18u); _indicies.push_back(19u); // Triangle 10

	_indicies.push_back(20u); _indicies.push_back(21u); _indicies.push_back(22u); // Triangle 11 +x
	_indicies.push_back(20u); _indicies.push_back(22u); _indicies.push_back(23u); // Triangle 12
}

void Mesh::GeneratePrimativeSphere(std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies)
{
	// Number of sub divisions to use
	const unsigned int subDivisions = 20;

	// Radius
	const float radius = 0.5f;

	// firstly calculate the top and bottom vertices's
	const Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	const Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	_verticies.push_back(topVertex);

	const float phiStep = m_pi / subDivisions;
	const float thetaStep = 2.0f * m_pi / subDivisions;

	// Compute the vertices's for every ring
	for (unsigned int i = 1; i <= subDivisions - 1; i++)
	{
		const float phi = i * phiStep;

		// Compute the vertices's of the current ring
		for (unsigned int j = 0; j <= subDivisions; j++)
		{
			const float theta = j * thetaStep;
			Vertex vertex;

			// Position
			vertex.m_position.m_x = radius * sinf(phi) * cosf(theta);
			vertex.m_position.m_y = radius * cosf(phi);
			vertex.m_position.m_z = radius * sinf(phi) * sinf(theta);

			// Tangent
			vertex.m_tangent.m_x = -radius * sinf(phi) * sinf(theta);
			vertex.m_tangent.m_y = 0.0f;
			vertex.m_tangent.m_z = +radius * sinf(phi) * cosf(theta);

			// Normalize the tangent
			vertex.m_tangent = vertex.m_tangent.normalize();

			// Calculate the normal
			vertex.m_normal = vertex.m_position.normalize();

			vertex.m_uv.m_x = theta / m_pi;
			vertex.m_uv.m_y = phi / m_pi;

			_verticies.push_back(vertex);
		}
	}

	_verticies.push_back(bottomVertex);

	// Calculate the indices's
	// Add the bottom vertex first
	for (unsigned int i = 1; i <= subDivisions; ++i)
	{
		_indicies.push_back(0);
		_indicies.push_back(i + 1);
		_indicies.push_back(i);
	}

	// Calculate the indices's for all the stacks
	unsigned int baseIndex = 1;
	unsigned int ringVertexCount = subDivisions + 1;
	for (unsigned int i = 0; i < subDivisions - 2; ++i)
	{
		for (unsigned int j = 0; j < subDivisions; ++j)
		{
			_indicies.push_back(baseIndex + i * ringVertexCount + j);
			_indicies.push_back(baseIndex + i * ringVertexCount + j + 1);
			_indicies.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			_indicies.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			_indicies.push_back(baseIndex + i * ringVertexCount + j + 1);
			_indicies.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	// Add the top separately
	const unsigned int southPoleIndex = static_cast<unsigned int>(_verticies.size() - 1);
	baseIndex = southPoleIndex - ringVertexCount;
	for (unsigned int i = 0; i < subDivisions; ++i)
	{
		_indicies.push_back(southPoleIndex);
		_indicies.push_back(baseIndex + i);
		_indicies.push_back(baseIndex + i + 1);
	}
}

void Mesh::LoadMeshWithAssImp(const std::string _filePath, std::vector<Vertex>& _verticies, std::vector<unsigned int>& _indicies)
{
	// Load the mesh from file
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_filePath, aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph);

	// Check to see if mesh loaded
	if (scene == nullptr)
	{
		throw std::runtime_error("Cannot load the mesh file: " + _filePath);
	}

	const aiMesh* aiMesh = scene->mMeshes[0];

	// Read the assimp mesh into this engines vertex format
	// Vertices
	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.m_position.m_x = aiMesh->mVertices[i].x;
		vertex.m_position.m_y = aiMesh->mVertices[i].y;
		vertex.m_position.m_z = aiMesh->mVertices[i].z;

		if (aiMesh->HasNormals())
		{
			vertex.m_normal.m_x = aiMesh->mNormals[i].x;
			vertex.m_normal.m_y = aiMesh->mNormals[i].y;
			vertex.m_normal.m_z = aiMesh->mNormals[i].z;
		}

		if (aiMesh->HasTangentsAndBitangents())
		{
			vertex.m_tangent.m_x = aiMesh->mTangents[i].x;
			vertex.m_tangent.m_y = aiMesh->mTangents[i].y;
			vertex.m_tangent.m_z = aiMesh->mTangents[i].z;
		}

		// UV
		if (aiMesh->HasTextureCoords(0u))
		{
			vertex.m_uv.m_x = aiMesh->mTextureCoords[0][i].x;
			vertex.m_uv.m_y = aiMesh->mTextureCoords[0][i].y;
		}

		_verticies.push_back(vertex);
	}

	// Indices
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		const aiFace face = aiMesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			_indicies.push_back(face.mIndices[j]);
	}
}