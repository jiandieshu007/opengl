#ifndef _SHADER_H_
#define _SHADER_H_

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class shader {
public:
	unsigned int programid;
	shader(const char* vertexpath, const char* fragmentpath);
	void use();
	void setbool(const std::string& name, bool val) const;
	void setfloat(const std::string& name, float val) const;
	void setint(const std::string& name, int val) const;
};



#endif