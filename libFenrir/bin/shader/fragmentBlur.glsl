#version 410

in vec2 texture_coordinates;

uniform sampler2D hbao_texture;

//Cor final do fragmento
layout(location=0) out vec4 blur_colour;

const int blurSize = 4; // use size of noise texture (4x4)

void main() {
	
	vec2 texelSize = 1.0 / vec2(textureSize(hbao_texture, 0));
	float result = 0.0;
	for (int x = 0; x < blurSize; ++x) 
	{
	   for (int y = 0; y < blurSize; ++y) 
	   {
	      vec2 offset = (vec2(-2.0) + vec2(float(x), float(y))) * texelSize;
	      result += texture(hbao_texture, texture_coordinates + offset).r;
	   }
	}
	
	result = result / float(blurSize * blurSize);

	blur_colour = vec4(result,result,result,1);
};