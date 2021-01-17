#version 330

layout(location = 0) out vec4 frag_color;

in vec2 texCoord;

void main() {
	frag_color = vec4(texCoord,0.f,1.f);
}