#version 440

layout(location = 0) in vec2  in_position;

out vec2 texCoord;
void main() {
    float x = -1.f + float((gl_VertexID & 1) << 2);
    float y = -1.f + float((gl_VertexID & 2) << 1);
    texCoord.x = (x+1.f)*0.5f;
    texCoord.y = -0.5f*y+0.5f; //flip vertically
    gl_Position = vec4(x, y, 0, 1);
}
