#pragma once
#include "Types.h"

class IndexBuffer
{
public:
	IndexBuffer(u32 maxIndices);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	u32 getCount() const { return m_count; }

private:
	u32 m_count;
	u32 m_rendererID;
};
