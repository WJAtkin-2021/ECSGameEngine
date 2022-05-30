#pragma once
#include <vector>
#include <memory>
#include "Vertex.h"

class GPUBuffers
{
public:
	virtual ~GPUBuffers();

	static std::shared_ptr<GPUBuffers> FactoryCreateGPUBuffers();

	virtual void GenerateBuffers() = 0;
	virtual void SetBuffersForDrawCall() = 0;

	void AppendVertex(Vertex _vertex);
	void AppendIndex(unsigned int _index);
	void SetVertexVector(std::vector<Vertex> _verticies);
	void SetIndexVector(std::vector<unsigned int> _indicies);

	int GetNumberOfIndicies() { return static_cast<int>(m_indicies.size()); }

protected:
	GPUBuffers();

	std::vector<unsigned int> m_indicies;
	std::vector<Vertex> m_verticies;
};