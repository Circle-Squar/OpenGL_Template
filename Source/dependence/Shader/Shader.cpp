#include "Shader.h"


Shader::Shader(const char* vShaderPath, const char* fShaderPath) {
	this->vShaderPath = vShaderPath;
	this->fShaderPath = fShaderPath;
	compile();
}
Shader::Shader() {
	vShaderPath = NULL;
	fShaderPath = NULL;
	ID = glCreateProgram();
}
void Shader::setVShader(const char* vShaderPath) {
	this->vShaderPath = vShaderPath;
}
void Shader::setFShader(const char* fShaderPath) {
	this->fShaderPath = fShaderPath;
}

int Shader::compile() {
	if (PathCheck() && FileCheck()) {
		// ..:: Read Files ::..

		std::string vertCode;
		std::string fragCode;
		std::ifstream vertShaderFile;
		std::ifstream fragShaderFile;

		vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// ..:: Open Files ::..
			vertShaderFile.open(vShaderPath);
			fragShaderFile.open(fShaderPath);
			std::stringstream vShaderStream, fShaderStream;

			// ..:: Read Files ::..
			vShaderStream << vertShaderFile.rdbuf();
			fShaderStream << fragShaderFile.rdbuf();

			// ..:: Close Files ::..
			vertShaderFile.close();
			fragShaderFile.close();

			// ..:: To str ::..
			vertCode = vShaderStream.str();
			fragCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "[ERROR] : Failed to read shader source file!" << std::endl;
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();

		// ..:: Compile Shader ::..
		unsigned int vertex, fragment;

		// Vertex
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		if (!CompileCheck(vertex)) {
			std::cout << "[ERROR] : Vertex Shader Compile Failed!" << std::endl;
			return -1;
		}

		// Fragment
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		if (!CompileCheck(fragment)) {
			std::cout << "[ERROR] : Fragment Shader Compile Failed!" << std::endl;
			return -1;
		}

		// ..:: Link Shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, InfoLog);
			std::cout << "[ERROR] : ..:: Shader Program Link Error" << std::endl << InfoLog << "[ERROR] : ..:: Shader Program Link Error ::.." << std::endl;
			return -1;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		std::cout << "[INFO] : Shader Compile Comlete, ID : " << ID << std::endl;
		return 0;
	}
	else {
		std::cout << "[ERROR] : Failed to find or read Shader files! " << std::endl;
		return -1;
	}
}

void Shader::use() {
	glUseProgram(ID);
}



// ..:: Files Check ::..
bool  Shader::PathCheck() {
	if (vShaderPath == NULL) {
		std::cout << "[ERROR] : Vertex Shader path is NULL!" << std::endl;
		return false;
	}
	if (fShaderPath == NULL) {
		std::cout << "[ERROR] : Fragment Shader path is NULL!" << std::endl;
		return false;
	}
	return true;
}
bool Shader::FileCheck() {
	std::ifstream VChecker(vShaderPath);
	if (!VChecker) {
		std::cout << "[ERROR] : Vertex Shader source file not found : " << vShaderPath << std::endl;
		return false;
	}
	std::ifstream FChecker(fShaderPath);
	if (!FChecker) {
		std::cout << "[ERROR] : Fragment Shader source file not found : " << fShaderPath << std::endl;
		return false;
	}
	return true;
}



// ..:: Uniform Set ::..
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
//====================================================================
void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
//====================================================================
void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
//====================================================================
void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z,
	float w) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
//====================================================================
void Shader::setMat2(const std::string& name, glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
		&mat[0][0]);
}

void Shader::setMat3(const std::string& name, glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
		&mat[0][0]);
}

void Shader::setMat4(const std::string& name, glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
		&mat[0][0]);
}

// ..:: Compile Check ::..
int Shader::CompileCheck(unsigned int& Shader) {
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(Shader, 512, NULL, InfoLog);
		std::cout << "[ERROR] ..:: Shader Compile Error ::.." << std::endl << InfoLog << "[ERROR] ..:: Shader Compile Error" << std::endl;
		return 0;
	}
	return 1;
}
