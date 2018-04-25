#version 330 core
// Input from vert shader
in vec2 UV;

// Output
out vec4 FragColor;

// Uniform values are constant for whole mesh
uniform sampler2D texture;

void main() {
	vec4 color = texture2D(texture, UV);
	FragColor = vec4(color.r, color.r, color.r, 1.0);
}