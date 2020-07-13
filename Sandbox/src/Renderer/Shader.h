#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* filePath);
	Shader(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniformInt(const char* name, int value);
	void SetUniformInt2(const char* name, const glm::ivec2& value);
	void SetUniformInt3(const char* name, const glm::ivec3& value);
	void SetUniformInt4(const char* name, const glm::ivec4& value);

	void SetUniformFloat(const char* name,  float value);
	void SetUniformFloat2(const char* name, const glm::vec2& value);
	void SetUniformFloat3(const char* name, const glm::vec3& value);
	void SetUniformFloat4(const char* name, const glm::vec4& value);

	void SetUniformMat3(const char* name, const glm::mat3& value);
	void SetUniformMat4(const char* name, const glm::mat4& value);
private:
	uint32_t GetUniformLocation(const char* name);

	static std::string ReadFile(const char* filePath);
	static std::unordered_map<GLenum, std::string> ParseShaderSource(const std::string& source);
	void Compile(const std::string& vertexSrc, const std::string& fragmentSrc);
private:
	uint32_t m_RendererID;
	std::unordered_map<std::string, uint32_t> m_UniformCache;
	
	static std::unordered_map<std::string, uint32_t> s_ShaderIDCache;
};