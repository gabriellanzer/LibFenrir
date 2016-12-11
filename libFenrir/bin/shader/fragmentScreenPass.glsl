#version 410

in vec2 texture_coordinates;

uniform sampler2D rgb_texture;
uniform sampler2D normals_texture;
uniform sampler2D depth_texture;
uniform sampler2D hbao_texture;
uniform sampler2D blur_texture;
uniform float zNear;
uniform float zFar;
uniform int mode;

out vec4 frag_colour;
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * zNear) / (zFar + zNear - z * (zFar - zNear));	
}

void main() {
	if(mode == 0)
	{
		frag_colour = texture(rgb_texture, vec2(texture_coordinates.x, texture_coordinates.y));
	}
	else if(mode == 1)
	{
		frag_colour = texture(normals_texture, vec2(texture_coordinates.x, texture_coordinates.y));
	}
	else if(mode == 2)
	{
		vec4 frag_depth = texture(depth_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		frag_colour = vec4(vec3(LinearizeDepth(frag_depth.r)), 1.0);
	}
	else if (mode == 3)
	{
		vec4 rgb_ = texture(rgb_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		vec4 depth_ = texture(depth_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		depth_  = vec4(vec3(LinearizeDepth(depth_.r)), 1.0);
		frag_colour =  rgb_ * depth_; 
	}
	else if (mode == 4)
	{
		vec4 rgb_ = texture(hbao_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		frag_colour =  rgb_; 
	}
	else if (mode == 5)
	{
		vec4 rgb_ = texture(blur_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		frag_colour =  rgb_; 
	}
	else if (mode == 6)
	{
		vec4 rgb_ = texture(rgb_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		vec4 hbao_ = texture(blur_texture, vec2(texture_coordinates.x, texture_coordinates.y));
		frag_colour =  rgb_ * hbao_; 
	}
};