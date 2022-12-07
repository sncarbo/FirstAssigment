#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"

class ShadersProgram
{
	public:
		ShadersProgram();
		~ShadersProgram();

		unsigned int GetShaderProgramId() const;

	private:
		char *LoadShaderSource(const char *shader_file_name);
		unsigned CompileShader(const unsigned & type, const char *source);
		unsigned CreateProgram(const unsigned & vtx_shader, const unsigned & frg_shader);

	private:
		unsigned int shaderProgramId;
		unsigned int vertexShader;
		unsigned int fragmentShader;
};