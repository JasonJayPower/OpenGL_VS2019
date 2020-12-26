#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 acolor;

out vec2 vTexCoord;
out vec4 vColor;
uniform mat4 viewProjection;

void main() {
    vColor = acolor;
    vTexCoord = texCoord;
    gl_Position = viewProjection * vec4(position.xy, 0.0, 1.0);
};