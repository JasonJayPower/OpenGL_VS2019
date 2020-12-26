#include "IndexBuffer.h"
#include <glad/glad.h>
#include <vector>

IndexBuffer::IndexBuffer(u32 maxIndices)
	: m_count     { maxIndices }
	, m_rendererID{ 0 }
{
	std::vector<u32> ind(maxIndices);
	u32 offset = 0;
	for (auto i = 0; i < maxIndices; i += 6)
	{
		ind[i + 0] = offset + 0;
		ind[i + 1] = offset + 1;
		ind[i + 2] = offset + 2;
		ind[i + 3] = offset + 2;
		ind[i + 4] = offset + 3;
		ind[i + 5] = offset + 0;
		offset += 4;
	}

	glCreateBuffers(1, &m_rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(u32), ind.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_rendererID);
}
void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
