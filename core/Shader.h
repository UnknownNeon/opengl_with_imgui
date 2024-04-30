#pragma once
#include "Util.h"
#include "glad/glad.h"

#include "Colors.h"
#include "iostream"

class Shader
{
	int ID = -1;
	unsigned int vshader=0;
	unsigned int fshader=0;

public:
	void load_shader(std::string path_to_file);
	void load_shader_manual(std::string vertex, std::string fragment);

	void init_and_use_shader();
	void setColor(const float COLOR[]);

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;


public:
	inline void use() { glUseProgram(ID); };
	inline int getShaderID() const { return ID; }


	
private:
	int shader_compile_result(unsigned int shader);
};