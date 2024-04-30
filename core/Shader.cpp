#include "Shader.h"


void Shader::load_shader(std::string path_to_file)
{
	std::string temp = Util::file_read(path_to_file);
	const char* AShader = temp.c_str();

	if (Util::getFileExt(path_to_file) == "vert") {
		vshader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vshader, 1, &AShader, NULL);
		shader_compile_result(vshader);
	}
	if (Util::getFileExt(path_to_file) == "frag") {
		fshader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fshader, 1, &AShader, NULL);
		shader_compile_result(fshader);
	}

	
}
void Shader::load_shader_manual(std::string vertex, std::string fragment) {

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* AShader = fragment.c_str();
	glShaderSource(fshader, 1, &AShader, NULL);
	shader_compile_result(fshader);

	vshader = glCreateShader(GL_VERTEX_SHADER);
	AShader = vertex.c_str();
	glShaderSource(vshader, 1, &AShader, NULL);
	shader_compile_result(vshader);

}

int Shader::shader_compile_result(unsigned int Shader)
{
	glCompileShader(Shader);
	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << 
			infoLog << std::endl;
	}
	return success;
}


void Shader::init_and_use_shader()
{
	ID = glCreateProgram();
	if (vshader != 0)
		glAttachShader(ID, vshader);
	else
		std::cout << "[Vertex shader not found]" << std::endl;
	if (fshader != 0)
		glAttachShader(ID, fshader);
	else
		std::cout << "[Fragment shader not found]" << std::endl;

	glLinkProgram(ID);
	/*Todo error checking for shader linkage */

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK_FAILED\n" <<
			infoLog << std::endl;
	}

	glUseProgram(ID);
	glEnable(GL_DEPTH_TEST);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	setMat4("view", glm::mat4(1.f));
	setMat4("model", glm::mat4(1.f));
	setMat4("projection", glm::mat4(1.f));

}



void Shader::setColor(const float COL[])
{
	int colorLocation = glGetUniformLocation(ID, "myColor");
	glUniform4fv(colorLocation,1,COL);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
