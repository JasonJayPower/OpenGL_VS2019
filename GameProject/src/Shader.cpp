
#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include "Utility.h"

Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

void Shader::bind()
{
    glUseProgram(m_rendererID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::compile(const std::string& vsFilePath, const std::string& fsFilePath)
{
    const auto vsStr = Utils::readFile(vsFilePath);
    const auto fsStr = Utils::readFile(fsFilePath);

    u32 vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, Utils::StringHelper(vsStr), nullptr);
    glCompileShader(vs);
    checkCompileErrors(vs, "VERTEX");

    u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, Utils::StringHelper(fsStr), nullptr);
    glCompileShader(fs);
    checkCompileErrors(fs, "FRAGMENT");

    m_rendererID = glCreateProgram();
    glAttachShader(m_rendererID, vs);
    glAttachShader(m_rendererID, fs);
    glLinkProgram(m_rendererID);
    checkCompileErrors(m_rendererID, "PROGRAM");

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::setVec2f(const std::string& name, const glm::vec2& vec2)
{
    glUniform2f(glGetUniformLocation(m_rendererID, name.c_str()), vec2.x, vec2.y);
}

void Shader::setVec3f(const std::string& name, const glm::vec3& vec3)
{
    glUniform3f(glGetUniformLocation(m_rendererID, name.c_str()), vec3.x, vec3.y, vec3.z);
}

void Shader::setVec4f(const std::string& name, const glm::vec4& vec4)
{
    glUniform4f(glGetUniformLocation(m_rendererID, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, false, glm::value_ptr(mat4));
}

void Shader::checkCompileErrors(u32 shader, const std::string& type)
{
    s32 success;
    s8 infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

