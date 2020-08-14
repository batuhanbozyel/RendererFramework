#include "pch.h"
#include <glad/glad.h>
#include "Shader.h"

#include <fstream>

std::unordered_map<std::string, uint32_t> Shader::s_ShaderIDCache;

Shader::Shader(const char* filePath)
	: m_RendererID(0)
{
	if (s_ShaderIDCache.find(filePath) == s_ShaderIDCache.end())
	{
		const std::string& source = ReadFile(filePath);
		auto& parsedSource = ParseShaderSource(source);
		Compile(parsedSource[GL_VERTEX_SHADER], parsedSource[GL_FRAGMENT_SHADER]);
		s_ShaderIDCache.insert(std::pair<std::string, uint32_t>(filePath, m_RendererID));
	}
	else m_RendererID = s_ShaderIDCache[filePath];
}

// name parameter will be used to cache Shader
Shader::Shader(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc)
	: m_RendererID(0)
{
	if (s_ShaderIDCache.find(name) == s_ShaderIDCache.end())
	{
		Compile(vertexSrc, fragmentSrc);
		s_ShaderIDCache.insert(std::pair<const char*, uint32_t>(name, m_RendererID));
	}
	else m_RendererID = s_ShaderIDCache[name];
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniformInt(const char* name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformInt2(const char* name, const glm::ivec2& value)
{
	glUniform2i(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniformInt3(const char* name, const glm::ivec3& value)
{
	glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniformInt4(const char* name, const glm::ivec4& value)
{
	glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniformFloat(const char* name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformFloat2(const char* name, const glm::vec2& value)
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniformFloat3(const char* name, const glm::vec3& value)
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniformFloat4(const char* name, const glm::vec4& value)
{
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMat3(const char* name, const glm::mat3& value)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1 ,GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

uint32_t Shader::GetUniformLocation(const char* name)
{
	auto& mapLocation = m_UniformCache.find(name);
	if (mapLocation == m_UniformCache.end())
	{
		uint32_t location = glGetUniformLocation(m_RendererID, name);
		LOG_ASSERT(location != -1, "Uniform could not found!");
		m_UniformCache.insert(std::pair<std::string, uint32_t>(name, location));
		return location;
	}
	return mapLocation->second;
}

std::string Shader::ReadFile(const char* filePath)
{
	std::string source;
	std::ifstream shaderFile(filePath, std::ios::in | std::ios::binary);
	if (shaderFile)
	{
		shaderFile.seekg(0, std::ios::end);
		size_t size = shaderFile.tellg();
		if (size != -1)
		{
			source.resize(size);
			shaderFile.seekg(0, std::ios::beg);
			shaderFile.read(&source[0], size);
			shaderFile.close();
		}
		else
		{
			LOG_ASSERT(false, "Could not read from file!");
		}
	}
	else
	{
		// Could not open file
		LOG_ASSERT(false, "Could not open file!");
	}
	return source;
}

std::unordered_map<uint32_t, std::string> Shader::ParseShaderSource(const std::string& source)
{
	auto ShaderType = [](const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		return 0;
	};

	std::unordered_map<uint32_t, std::string> shaderSources;

	size_t begin = source.find("#type", 0);
	while (begin != std::string::npos)
	{
		size_t end = source.find_first_of("\r\n", begin);
		// Syntax error
		LOG_ASSERT(end != std::string::npos, "Shader program: Syntax Error!");
		begin = begin + strlen("#type") + 1;
		std::string type = source.substr(begin, end - begin);
		// Invalid shader type
		LOG_ASSERT(ShaderType(type), "Invalid Shader type!");
		
		begin = source.find_first_not_of("\r\n", end);
		//  Syntax error
		LOG_ASSERT(begin != std::string::npos, "Shader program: Syntax Error!");
		end = source.find("#type", begin);

		shaderSources[ShaderType(type)] = (end == std::string::npos) ? source.substr(begin) : source.substr(begin, end - begin);
		begin = end;
	}
	return shaderSources;
}

void Shader::Compile(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const char* source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Vertex shader compilation failed
		LOG_ERROR("Vertex Shader complation failed: {0}", infoLog.data());
		LOG_ASSERT(false, "Vertex Shader compilation failed!");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Fragment shader compilation failed
		LOG_ERROR("Fragment Shader compilation failed: {0}", infoLog.data());
		LOG_ASSERT(false, "Fragment Shader compilation failed!");
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link our program
	glLinkProgram(m_RendererID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_RendererID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Shader linking failed
		LOG_ERROR("Shader Linking failed: {0}", infoLog.data());
		LOG_ASSERT(false, "Shader Linking failed!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_RendererID, vertexShader);
	glDetachShader(m_RendererID, fragmentShader);
}
