#include "Renderer.h"
#include "glad/glad.h"

Renderer::Renderer()
	: m_drawCalls { 0 }
	, m_vertexCount{ 0 }
	, m_indicesCount { 0 }
	, m_vao{ }
	//, m_mbo{ MaxVertices }
	, m_vbo{ MaxVertices } 
	, m_ibo{ MaxIndices }
	, m_vertexData { new Vertex[MaxVertices]}
	//, m_vertexData{ m_mbo.getBufferData() }
	//, m_bufferLockManager { MaxVertices }
{
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::batchBegin()
{
	startBatch();
}

void Renderer::batchDraw(Texture tex, const glm::vec4& dst)
{

	if (m_vertexCount >= MaxVertices) {
		nextBatch();
	}
	m_vertexData[m_vertexCount++] = { {dst.x, dst.y}, {0,0}, {255, 255,0, 255} };
	m_vertexData[m_vertexCount++] = { {dst.x, dst.y + dst.w }, {0, 1 }, {255, 255,0, 255} };
	m_vertexData[m_vertexCount++] = { {dst.x + dst.z, dst.y + dst.w}, {1, 1}, {255, 255,0, 255} };
	m_vertexData[m_vertexCount++] = { {dst.x + dst.z, dst.y}, {1, 0}, {255, 255,0, 255} };
	m_indicesCount += 6;


	//if (m_vertexCount >= MaxVertices + m_bufferLockManager.getBufferOffset()) {
	//	nextBatch();
	//}
	//m_vertexData[m_vertexCount++] = { {dst.x, dst.y + dst.w }, {0, 1 }, {255, 255,0, 255} };
	//m_vertexData[m_vertexCount++] = { {dst.x + dst.z, dst.y + dst.w}, {1, 1}, {255, 255,0, 255} };
	//m_vertexData[m_vertexCount++] = { {dst.x, dst.y}, {0,0}, {255, 255,0, 255} };

	//m_vertexData[m_vertexCount++] = { {dst.x + dst.z, dst.y + dst.w}, {1, 1}, {255, 255,0, 255} };
	//m_vertexData[m_vertexCount++] = { {dst.x + dst.z, dst.y}, {1, 0}, {255, 255,0, 255} };
	//m_vertexData[m_vertexCount++] = { {dst.x, dst.y}, {0,0}, {255, 255,0, 255} };
}

void Renderer::batchEnd()
{
	flush();
	// std::cout << m_drawCalls << std::endl;
	m_drawCalls = 0;

}

void Renderer::startBatch()
{
	m_vertexCount = 0;
	m_indicesCount = 0;

	//m_vertexCount = m_bufferLockManager.getBufferOffset();
	//m_bufferLockManager.wait();
}

void Renderer::nextBatch()
{
	flush();
	startBatch();
}

void Renderer::flush()
{
	if (m_vertexCount != 0) {
		m_vbo.updateBuffer(m_vertexCount * sizeof(Vertex), m_vertexData);
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, nullptr);
	}

	//if (m_vertexCount != 0) {
	//	glDrawArrays(GL_TRIANGLES, m_bufferLockManager.getBufferOffset(), m_vertexCount);
	//	m_bufferLockManager.lock();
	//}

	++m_drawCalls;
}

void Renderer::clear() const
{
	//glClear(0.f,0.f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
}
