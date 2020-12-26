#pragma once

#include "Types.h"

#include <array>
#include <glad/glad.h>

struct BufferLock {
    u32 offset;
    GLsync sync;
};

class BufferLockManager {
public:
    BufferLockManager(u32 vertexCount);

    void lock();
    void wait();
    u32 getBufferOffset() const { return m_bufferLocks[m_bufferIndex].offset; }

private:
    static constexpr auto MaxBufferLocks = 3;
    static constexpr auto OneSecToNano   = 1000000000;
    u32 m_bufferIndex;
    std::array<BufferLock, MaxBufferLocks> m_bufferLocks;
};