#version 410

in vec4 fragment_light_colour;
in vec3 color;

// fixed point light properties


//Cor final do fragmento
out vec4 frag_colour;

void main () {
	
	frag_colour = mix(fragment_light_colour, vec4 (color, 1.0), 0.5);
};