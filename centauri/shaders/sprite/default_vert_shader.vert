#version 330 core
// input different for every execution of this shader
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output to frag shader
out vec2 UV;

// Uniform values are constant for whole mesh
uniform mat4 MVP;
uniform vec2 UVoffset;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	UV = vertexUV + UVoffset;
}