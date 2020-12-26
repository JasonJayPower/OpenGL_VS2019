#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "Types.h"
#include "Vertex.h"

class MapBuffer
{
public:
	MapBuffer(u32 size);
	~MapBuffer();

	Vertex* getBufferData() const { return m_bufferData; }
	void bind() const;
	void unbind() const;
	void lockBuffer(GLsync& sync);
	void waitBuffer(GLsync& sync);

private:
	u32 m_rendererID;
	u32 m_mapFlags;
	u32 m_createFlags;
	Vertex* m_bufferData;
};
