#pragma once

#include "Types.h"
#include <glm/vec2.hpp>
#include <glm/gtc/type_precision.hpp>

struct Tex {
	u16 x, y;
};

struct Color {
	u8 r, g, b, a;
};

struct Vertex {
	glm::vec2 pos;
	Tex tex;
	Color col;
};