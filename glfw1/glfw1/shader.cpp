#include "shader.h"

shader::shader(const char* vertexpath, const char* fragmentpath)
{
	std::string vertex, fragment;
	try {
		std::ifstream vsfile(vertexpath), fsfile(fragmentpath);
		// 指定发生什么时抛出异常
		vsfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fsfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		std::stringstream vsstream, fsstream;
		vsstream << vsfile.rdbuf();
		fsstream << fsfile.rdbuf();
		vsfile.close(), fsfile.close();
		vertex = vsstream.str();
		fragment = fsstream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	int success;
	char infolog[512];
	const char* vscode = vertex.c_str();
	const char* fscode = fragment.c_str();
	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER), fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexshader, sizeof(vscode), &vscode, NULL);
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexshader, 512, NULL, infolog);
		std::cout << infolog << std::endl;
		exit(1);
	}

	glShaderSource(fragmentshader, sizeof(fscode), &fscode, NULL);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentshader, 512, nullptr, infolog);
		std::cout << infolog << std::endl;
		exit(1);
	}

	programid = glCreateProgram();
	glAttachShader(programid, vertexshader);
	glAttachShader(programid, fragmentshader);
	glLinkProgram(programid);
	glGetProgramiv(programid, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programid, 512, NULL, infolog);
		std::cout << infolog << std::endl;
		exit(1);
	}
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

}

void shader::use()
{
	glUseProgram(programid);
}

void shader::setbool(const std::string& name, bool val) const
{
	int loc = glGetUniformLocation(programid, name.c_str() );
	glUniform1i(loc, val);
}

void shader::setfloat(const std::string& name, float val) const
{
	int loc = glGetUniformLocation(programid, name.c_str());
	glUniform1f(loc, val);
}

void shader::setint(const std::string& name, int val) const
{
	int loc = glGetUniformLocation(programid, name.c_str());
	glUniform1i(loc, val);
}
