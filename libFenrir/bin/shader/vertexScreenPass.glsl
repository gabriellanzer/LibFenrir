#version 410

layout(location=0) in vec3 vp;
layout(location=1) in vec2 vt;

out vec2 texture_coordinates;

void main () {
	texture_coordinates = vt;
	gl_Position = vec4 (vp.x * 2.0 - 1.0, vp.y * 2.0 - 1.0, 0, 1.0);
};