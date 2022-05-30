#include "GPUBuffers.h"
#include "GPUBuffers_DX11.h"

GPUBuffers::GPUBuffers()
{

}

GPUBuffers::~GPUBuffers()
{

}

std::shared_ptr<GPUBuffers> GPUBuffers::FactoryCreateGPUBuffers()
{
#ifdef BUILD_DX_11
	return std::shared_ptr<GPUBuffers>(new GPUBuffers_DX());
#elif BUILD_OpenGL
	return std::shared_ptr<GPUBuffers>(new GPUBuffers_GL());
#endif // BUILD_DX_11
}

void GPUBuffers::AppendVertex(Vertex _vertex)
{
	m_verticies.push_back(_vertex);
}

void GPUBuffers::AppendIndex(unsigned int _index)
{
	m_indicies.push_back(_index);
}

void GPUBuffers::SetVertexVector(std::vector<Vertex> _verticies)
{
	m_verticies.clear();
	m_verticies = _verticies;
}

void GPUBuffers::SetIndexVector(std::vector<unsigned int> _indicies)
{
	m_indicies.clear();
	m_indicies = _indicies;
}