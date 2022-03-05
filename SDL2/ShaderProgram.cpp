#include "ShaderProgram.h"
#include <glad/glad.h>
#include <stdexcept>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vFilename, const char* fFilename)
{
	const char* vertexShaderSource = nullptr;
	const char* fragmentShaderSource = nullptr;

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.open(vFilename);
	fShaderFile.open(fFilename);
	std::stringstream vShaderStream, fShaderStream;
	// read file's buffer contents into streams
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	// close file handlers
	vShaderFile.close();
	fShaderFile.close();
	// convert stream into string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();
	vertexShaderSource = vertexCode.c_str();
	fragmentShaderSource = fragmentCode.c_str();

	if (vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
	{
		throw std::runtime_error("shader source was nullptr");
	}

	int success;

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLsizei logLength;
		GLchar  log[1024];
		glGetShaderInfoLog(vertexShader, sizeof(log), &logLength, log);
		std::string loginfo(log, logLength);
		throw std::runtime_error("failed to compile vertex shader : " +loginfo);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLsizei logLength;
		GLchar  log[1024];
		glGetShaderInfoLog(fragmentShader, sizeof(log), &logLength, log);
		std::string loginfo(log, logLength);
		throw std::runtime_error("failed to compile fragment shader : " +loginfo);
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		throw std::runtime_error("failed to link shader!");
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (glGetError() != GL_NO_ERROR)
	{
		throw std::runtime_error("failed to initialize shader program!");
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

void ShaderProgram::Use() const
{
	glUseProgram(id);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void ShaderProgram::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
