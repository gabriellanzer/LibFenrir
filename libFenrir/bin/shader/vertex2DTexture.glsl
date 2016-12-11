#version 410
layout(location=0) in vec3 vp;
layout(location=1) in vec2 vt;
uniform mat4 model;
out vec2 texture_coordinates;
void main () {
	texture_coordinates = vt;
	gl_Position = model * vec4 (vp, 1.0);
};