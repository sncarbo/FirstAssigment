#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "Math/float4x4.h"

#define DEBUG_DRAW_IMPLEMENTATION
#include "DebugDraw.h"
#include "SDL.h"

#include "glew.h"


class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

    public:
        ModuleDebugDraw();
        ~ModuleDebugDraw();

	    bool Init();
	    update_status Update();
	    bool CleanUp();

        void DrawSquareGrid(float mins, float maxs, float y, float step, ddVec3_In color);
        void Draw(const float4x4& view, const float4x4& proj, unsigned width, unsigned height);
    private:
        static DDRenderInterfaceCoreGL* implementation;
};
