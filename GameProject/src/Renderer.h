#pragma once

#include "Vertex.h"

#include "MapBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include <array>
#include <vector>
#include "BufferLock.h"

#include "Texture.h"

class Renderer {
public:
	Renderer();

	void batchBegin();
	void batchDraw(Texture tex, const glm::vec4& dst);
	void batchEnd();

	void startBatch();
	void nextBatch();
	void flush();

	void clear() const;
	void setClearColor(const glm::vec4& color) const;

private:
	static constexpr auto MaxSprites  = 1024;
	static constexpr auto MaxVertices = MaxSprites * 4;
	static constexpr auto MaxIndices  = MaxSprites * 6;

	u32 m_drawCalls;
	u32 m_vertexCount;
	u32 m_indicesCount;
	VertexArray m_vao;
	//MapBuffer m_mbo;
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;

	Vertex* m_vertexData;
	//BufferLockManager m_bufferLockManager;
};
//u32 m_bufferCount;
//IndexBuffer m_ibo;
//static constexpr auto MaxIndices = MaxSprites * 6;