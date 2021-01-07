#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
uniform mat4 modelMX;
uniform mat4 viewMX;
uniform mat4 projMX;

out vec3 uv;
out vec3 pos;
out vec3 normal;
void main()
{
    gl_Position = projMX*viewMX*modelMX*vec4(in_pos, 1.0);
    pos = mat3(modelMX)*in_pos;
    uv = in_pos;
    normal = inverse(transpose(mat3(modelMX)))*in_normal;
}