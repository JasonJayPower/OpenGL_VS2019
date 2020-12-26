#include "MapBuffer.h"
#include "Vertex.h"
#include <iostream>

MapBuffer::MapBuffer(u32 size)
	: m_rendererID{ 0 }
	, m_mapFlags{ GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT }
	, m_bufferData{ nullptr }
{
	glCreateBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glBufferStorage(GL_ARRAY_BUFFER, size * sizeof(Vertex) * 3, nullptr, m_mapFlags | GL_DYNAMIC_STORAGE_BIT);
	m_bufferData = static_cast<Vertex*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, size * sizeof(Vertex) * 3, m_mapFlags));
	

	//glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	//glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
}

MapBuffer::~MapBuffer()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glDeleteBuffers(1, &m_rendererID);
}

void MapBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void MapBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MapBuffer::lockBuffer(GLsync& sync)
{
	if (sync) {
		glDeleteSync(sync);
	}
	sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

void MapBuffer::waitBuffer(GLsync& sync)
{
	if (sync) {
		while (true) {
			GLenum waitReturn = glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
			if (waitReturn == GL_ALREADY_SIGNALED || waitReturn == GL_CONDITION_SATISFIED) {
				return;
			}
		}
	}
}
