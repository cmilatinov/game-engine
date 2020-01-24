#pragma once
#include "Shader.h"
class PrimitiveShader : public Shader {
	
	public:
		static const char * VERTEX_FILE, * FRAGMENT_FILE;
		unsigned int location_projViewMatrix, location_uniformColor, location_useUniformColor;

	public:
		PrimitiveShader();
		~PrimitiveShader();

		void bindAttributes();
		void getUniformLocations();

		inline void loadProjViewMatrix(const mat4 & matrix) {
			loadMatrix(location_projViewMatrix, &matrix);
		}

		inline void loadUseUniformColor(const bool & value) {
			loadBoolean(location_useUniformColor, value);
		}

		inline void loadUniformColor(const vec3 & value) {
			loadVector(location_uniformColor, &value);
		}

};

