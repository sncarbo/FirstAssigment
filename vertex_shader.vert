#version 430

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv0;


layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 model;

out vec2 uv0;

void main()
{
	gl_Position = proj*view*model*vec4(vertex_position, 1.0);
	uv0 = vertex_uv0;
}