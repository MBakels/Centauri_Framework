#version 330 core
// Input from vert shader
in vec2 UV;

// Output
out vec4 FragColor;

// Uniform values are constant for whole mesh
uniform sampler2D texture;

void main() {
	FragColor = texture2D(texture, UV);
}