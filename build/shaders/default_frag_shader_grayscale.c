#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform sampler2D texture;

void main() {
	vec4 color = texture2D(texture, UV);
	float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
	gl_FragColor = vec4(vec3(gray), 1.0);
}