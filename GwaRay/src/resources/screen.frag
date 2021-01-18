#version 440

layout(location = 0) out vec4 frag_color;

uniform sampler2D tex;
in vec2 texCoord;

void main() {
	frag_color = texture(tex,texCoord);
}