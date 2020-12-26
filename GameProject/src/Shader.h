#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>

#include "Types.h"

class Shader
{
public:
	Shader() = default;
	~Shader();

	void bind();
	void unbind();

	void compile(const std::string& vertexFilePath, const std::string& fragmentFilePath);

	void setVec2f(const std::string& name, const glm::vec2& value);
	void setVec3f(const std::string& name, const glm::vec3& value);
	void setVec4f(const std::string& name, const glm::vec4& value);
	void setMat4(const std::string& name, const glm::mat4& matrix);

	void checkCompileErrors(u32 shader, const std::string& type);


private:
	u32 m_rendererID;
};