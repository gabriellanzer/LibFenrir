#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vt;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 view, proj, model;

out vec2 texture_coordinates;
vec3 position_eye, normal_eye;
out vec4 fragment_light_colour;

// fixed point light properties
vec3 light_position_world  = vec3 (0.0, 0.0, 2.0);
vec3 Ls = vec3 (1.0, 1.0, 1.0); // white specular colour
vec3 Ld = vec3 (0.9, 0.9, 0.9); // dull white diffuse light colour
vec3 La = vec3 (0.5, 0.5, 0.5); // grey ambient colour

// surface reflectance
vec3 Ks = vec3 (1.0, 1.0, 1.0); // fully reflect specular light
vec3 Kd = vec3 (1.0, 0.5, 0.0); // orange diffuse surface reflectance
vec3 Ka = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light
float specular_exponent = 100.0; // specular 'power'

void main() {
	//Passar as Coordenadas do UV adiante
	texture_coordinates = vt;
	
	//Calcular a posição relativa à camera
	position_eye = vec3 (view * model * vec4 (vertex_position, 1.0));
	
	//Calcular a normal relativa à camera
	normal_eye = vec3 (view * model * vec4 (vertex_normal, 0.0));
	
	//Calcular a posição do vértice para rasterização
	gl_Position = proj * vec4 (position_eye, 1.0);

	
	// ambient intensity
	vec3 Ia = La * Ka;

	// diffuse intensity
	// raise light position to eye space
	vec3 light_position_eye = vec3 (view * vec4 (light_position_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize (distance_to_light_eye);
	float dot_prod = dot (direction_to_light_eye, normal_eye);
	dot_prod = max (dot_prod, 0.0);
	vec3 Id = Ld * Kd * dot_prod; // final diffuse intensity
	
	// specular intensity
	vec3 surface_to_viewer_eye = normalize (-position_eye);
	
	//vec3 reflection_eye = reflect (-direction_to_light_eye, normal_eye);
	//float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
	//dot_prod_specular = max (dot_prod_specular, 0.0);
	//float specular_factor = pow (dot_prod_specular, specular_exponent);
	
	// blinn
	vec3 half_way_eye = normalize (surface_to_viewer_eye + direction_to_light_eye);
	float dot_prod_specular = max (dot (half_way_eye, normal_eye), 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);
	
	vec3 Is = Ls * Ks * specular_factor; // final specular intensity
	
	// distance factor
	float dFactor = length(distance_to_light_eye);
	
	// final colour
	
	//fragment_light_colour = vec4 (Is + (Id + Ia)*1.0/dFactor, 1.0); // Linear
	
	fragment_light_colour = vec4 (Is + (Id + Ia)*1.0/pow(dFactor,2), 1.0); // Quadratic 

	//fragment_light_colour = vec4 (Is + (Id + Ia)*1.0/pow(dFactor,3), 1.0); // Cube 



};