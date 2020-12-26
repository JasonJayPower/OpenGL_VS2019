#include "BufferLock.h"

BufferLockManager::BufferLockManager(u32 vertexCount)
	: m_bufferIndex { 0 }
	, m_bufferLocks { 0 }
{
	for (u32 i = 0; i < MaxBufferLocks; ++i) {
		m_bufferLocks[i] = { i * vertexCount, nullptr };
	}
}

void BufferLockManager::lock()
{
	GLsync& sync = m_bufferLocks[m_bufferIndex].sync;
	if (sync) {
		glDeleteSync(sync);
	}
	sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	++m_bufferIndex %= MaxBufferLocks;
}

void BufferLockManager::wait()
{
	u32 waitFlags = 0;
	u64 waitDuration = 0;
	GLsync& sync = m_bufferLocks[m_bufferIndex].sync;

	if (sync) {
		while (true) {
			GLenum waitRet = glClientWaitSync(sync, waitFlags, waitDuration);
			if (waitRet == GL_ALREADY_SIGNALED || waitRet == GL_CONDITION_SATISFIED) {
				return;
			}

			waitFlags = GL_SYNC_FLUSH_COMMANDS_BIT;
			waitDuration = OneSecToNano;
		}
	}
}
