attribute vec3 vertPosition;
attribute vec3 vertNormal;
attribute vec2 vertUv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normal;

varying vec4 fragPosition;
varying vec4 fragNormal;
varying vec2 fragUv;

const mat4 M = mat4(
	vec4(0.5, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)
);

void main()
{
	fragUv = vertUv;
	fragPosition = vec4(vertPosition, 1.0);
	fragNormal = vec4(vertNormal, 0.0);
	
	gl_Position = fragPosition;
}