#version 410
//in vec2 texture_coordinates;
//uniform sampler2D basic_texture;
out vec4 frag_colour;

//n vec4 gl_FragCoord;


float zNear = 0.01f;
float zFar = 100.0;

  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));	
}


void main() {
	
	float depth = LinearizeDepth(gl_FragCoord.z) / (zFar); // divide by far for demonstration
	
    frag_colour = vec4(vec3(depth), 1.0f);
	
};