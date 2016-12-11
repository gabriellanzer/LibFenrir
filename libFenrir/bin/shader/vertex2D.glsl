#version 410
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vc;
uniform mat4 model;
out vec3 color;
void main () {
	color = vc;
	gl_Position = model * vec4 (vp, 1.0);
};