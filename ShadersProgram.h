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
		unsigned CompileShader(unsigned type, const char *source);
		unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);

	private:
		unsigned int shaderProgramId;
		unsigned int vertexShader;
		unsigned int fragmentShader;
};