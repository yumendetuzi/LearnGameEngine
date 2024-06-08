#include "Shader.h"
#include <glad/glad.h>
#include <vector>
#include "../Log.h"
#include "../Core.h"
namespace Hazel {

	Shader::Shader(const std::string& vertex, const std::string& fragment):mID(0)
	{
		GLuint ver = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertexC = vertex.c_str();
		glShaderSource(ver, 1, &vertexC, 0);
		glCompileShader(ver);
		GLint state = 0;
		glGetShaderiv(ver, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			GLint len = 0;
			glGetShaderiv(ver, GL_INFO_LOG_LENGTH, &len);
			std::vector<GLchar> vLog(len);
			glGetShaderInfoLog(ver, len, &len, &vLog[0]);
			glDeleteShader(ver);
			HZ_CORE_ERROR("{0}", vLog.data());
			HZ_CORE_ASSERT(false, "Vertex compile fail!");
			return ;
		}
		//fragmen
		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragC = fragment.c_str();
		glShaderSource(frag, 1, &fragC, 0);
		glCompileShader(frag);
		glGetShaderiv(frag, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			GLint len = 0;
			glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &len);
			std::vector<GLchar> vLog(len);
			glGetShaderInfoLog(frag, len, &len, &vLog[0]);
			glDeleteShader(frag);
			HZ_CORE_ERROR("{0}", vLog.data());
			HZ_CORE_ASSERT(false, "Fragment compile fail!");
			return;
		}
		//link
		mID = glCreateProgram();

		GLuint prog = mID;
		glAttachShader(prog, ver);
		glAttachShader(prog, frag);
		glLinkProgram(prog);
		glGetProgramiv(prog, GL_LINK_STATUS, &state);
		if (state == false)
		{
			GLint len = 0;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
			std::vector<GLchar> vLog(len);
			glGetProgramInfoLog(prog, len, &len, &vLog[0]);
			glDeleteShader(ver);
			glDeleteShader(frag);
			glDeleteProgram(prog);
			HZ_CORE_ERROR("{0}", vLog.data());
			HZ_CORE_ASSERT(false, "shader link fail!");
			return;
		}
		glDeleteShader(ver);
		glDeleteShader(frag);
	}

	Shader::~Shader()
	{
		glDeleteProgram(mID);
	}

	void Shader::Bind()
	{
		glUseProgram(mID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

}

