#version 410

in vec4 fragment_light_colour;
in vec2 texture_coordinates;

// Precisa da matriz de view e textura para mapeamento
uniform mat4 view;
uniform sampler2D basic_texture;



//Cor final do fragmento
out vec4 frag_colour;

void main () {
	
	// texture colour
	vec4 texel = texture(basic_texture, vec2(texture_coordinates.x, 1 - texture_coordinates.y));
	
	//frag_colour =  fragment_light_colour;
	
	//frag_colour = texel * fragment_light_colour;
	frag_colour = mix(texel, fragment_light_colour,0.5);
};