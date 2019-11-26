#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){

	// Code strings and file streams.
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	
	// Enable file stream exceptions.
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {

		// Open the shader source files.
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		
		// Read into code strings.
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		// Close the files.
		vShaderFile.close();
		fShaderFile.close();
		
		// Convert streams to strings.
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	} catch (ifstream::failure e) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	// String pointers.
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	// Create and compile vertex shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// Check shader for errors.
	if (!checkCompileErrors(vertex, "VERTEX")) exit(ERR_SHADER_COMPILATION);
	
	// Create and compile fragment shader.
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// Check shader for errors.
	if (!checkCompileErrors(fragment, "FRAGMENT")) exit(ERR_SHADER_COMPILATION);
	
	// Create shader program.
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
}
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	
	// Code strings and file streams.
	string vertexCode;
	string geometryCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream gShaderFile;
	ifstream fShaderFile;
	
	// Enable file stream exceptions.
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {

		// Open the shader source files.
		vShaderFile.open(vertexPath);
		gShaderFile.open(geometryPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, gShaderStream, fShaderStream;
		
		// Read into code strings.
		vShaderStream << vShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		// Close the files.
		vShaderFile.close();
		gShaderFile.close();
		fShaderFile.close();

		// Convert streams to strings.
		vertexCode = vShaderStream.str();
		geometryCode = gShaderStream.str();
		fragmentCode = fShaderStream.str();

	} catch (ifstream::failure e) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	// String pointers.
	const char *vShaderCode = vertexCode.c_str();
	const char *gShaderCode = geometryCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	// Create and compile vertex shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// Check shader for errors.
	if (!checkCompileErrors(vertex, "VERTEX")) exit(ERR_SHADER_COMPILATION);
	
	// Create and compile geometry shader.
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);

	// Check shader for errors.
	if (!checkCompileErrors(geometry, "GEOMETRY")) exit(ERR_SHADER_COMPILATION);

	// Create and compile fragment shader.
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// Check shader for errors.
	if (!checkCompileErrors(fragment, "FRAGMENT")) exit(ERR_SHADER_COMPILATION);

	// Create shader program.
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, geometry);
	glAttachShader(id, fragment);
}
Shader::~Shader(){
	glDetachShader(id, vertex);
	glDetachShader(id, geometry);
	glDetachShader(id, fragment);
	glDeleteShader(vertex);
	glDeleteShader(geometry);
	glDeleteShader(fragment);
	glDeleteProgram(id);
}

void Shader::use() {
	glUseProgram(id);
}
void Shader::stop() {
	glUseProgram(0);
}
void Shader::bindAttribute(int attribute, const char * varName) {
	glBindAttribLocation(id, attribute, varName);
}
unsigned int Shader::getUniformLocation(const char* name) {
	return glGetUniformLocation(id, name);
}

void Shader::loadBoolean(unsigned int location, bool boolean) {
	glUniform1i(location, boolean == true ? 1 : 0);
}
void Shader::loadInt(unsigned int location, int integer) {
	glUniform1i(location, integer);
}
void Shader::loadFloat(unsigned int location, float f) {
	glUniform1f(location, f);
}
void Shader::loadDouble(unsigned int location, double d) {
	glUniform1d(location, d);
}
void Shader::loadVector(unsigned int location, const vec3* vec) {
	glUniform3f(location, vec->x, vec->y, vec->z);
}
void Shader::loadVector(unsigned int location, const vec4* vec) {
	glUniform4f(location, vec->x, vec->y, vec->z, vec->w);
}
void Shader::loadMatrix(unsigned int location, const mat4* mat) {
	glUniformMatrix4fv(location, 1, false, mat->m);
}

bool Shader::checkCompileErrors(unsigned int shader, string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			return false;
		}

		return true;

	}
	else {

		glGetProgramiv(shader, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			return false;
		}

		return true;

	}
}

void Shader::validate() {

	// Bind shader attributes.
	bindAttributes();

	// Link and validate the shader program.
	glLinkProgram(id);
	glValidateProgram(id);

	// Check for any errors.
	if (!checkCompileErrors(id, "PROGRAM")) exit(ERR_SHADER_COMPILATION);

	// Retrieve any uniform variables' locations.
	getUniformLocations();

}