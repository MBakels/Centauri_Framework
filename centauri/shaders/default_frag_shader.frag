#version 330 core
// Input from vert shader
in vec2 UV;

// Uniform values are constant for whole mesh
uniform sampler2D texture;

void main() {
	// Output
	gl_FragColor = texture2D(texture, UV);
}