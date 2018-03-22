#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform sampler2D texture;

void main() {
	FragColor = texture2D(texture, UV);
}