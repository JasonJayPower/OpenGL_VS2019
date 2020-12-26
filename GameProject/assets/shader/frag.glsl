#version 450 core

out vec4 color;

in vec2 vTexCoord;
in vec4 vColor;

uniform sampler2D image;
void main() {
    vec4 textureColor = texture(image, vTexCoord);
    color = texture(image, vTexCoord) * vColor;
};