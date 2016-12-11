#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vc;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 view, proj, model;

out vec3 color, position_eye, normal_eye;


void main() {
	//Passar a cor do vértice adiante
	color = vc;
	
	//Calcular a posição relativa à camera
	position_eye = vec3 (view * model * vec4 (vertex_position, 1.0));
	
	//Calcular a normal relativa à camera
	normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
	
	//Calcular a posição do vértice para rasterização
	gl_Position = proj * vec4 (position_eye, 1.0);
};