#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "Types.h"
#include "Vertex.h"

class VertexBuffer
{
public:
	VertexBuffer(u32 maxVertices);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
	void updateBuffer(u32 size, const Vertex* const data) const;
private:
	u32 m_rendererID;
};
