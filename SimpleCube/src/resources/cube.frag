#version 450 core
uniform vec3 lightPos;
uniform vec3 viewPos;

layout(r32ui) coherent uniform uimage2D image;

out vec4 fragColor;
in vec3 pos;
in vec3 uv;
in vec3 normal;
void main()
{
	int tiles = 9;
	float epsilon = 0.0005f*(tiles);
    float cx = floor(tiles*uv.x-epsilon);
	float cy = floor(tiles*uv.y-epsilon);
	float cz = floor(tiles*uv.z-epsilon);
	float check = abs(mod(cx + cy + cz, 2.f));
	vec3 color = vec3(check);

	// ambient
    vec3 ambient = 0.05 * color;

	// diffuse
    vec3 lightDir = normalize(lightPos - pos);
    vec3 normal = normalize(normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
	// specular
    vec3 viewDir = normalize(viewPos- pos);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = spec*vec3(1,1,0.63);
	ivec2 coord = ivec2(gl_FragCoord.xy);

	fragColor = vec4(ambient+diffuse+specular,1.f);
	//fragColor = vec4(1,0,1,1);
} 