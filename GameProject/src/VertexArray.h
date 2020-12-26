#pragma once
#include "Types.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

private:
	u32 m_rendererID;
};