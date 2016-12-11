#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vt;
layout(location = 2) in vec3 vertex_normal;

uniform mat3 normal;
uniform mat4 view, proj, model;

out vec2 texture_coordinates;
out vec3 position_eye, normal_eye;
flat out vec3 vert_normal;

void main() {
	//Passar as Coordenadas do UV adiante
	texture_coordinates = vt;
	
	//Calcular a normal do objeto no espaço
	vert_normal = normalize((normal * vertex_normal).xyz);
	
	//Calcular a posição relativa à camera
	position_eye = vec3 (view * model * vec4 (vertex_position, 1.0));
	
	//Calcular a normal relativa à camera
	normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
	normal_eye = normalize(normal_eye);
	
	//Calcular a posição do vértice para rasterização
	gl_Position = proj * vec4 (position_eye, 1.0);
};