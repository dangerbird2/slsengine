attribute vec4 vertPosition;
attribute vec4 vertNormal;
attribute vec2 vertUv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normal;

varying vec4 fragPosition;
varying vec4 fragNormal;
varying vec2 fragUv;


void main()
{
	fragUv = vertUv;
	fragPosition = vertPosition;
	gl_Position = vec4(vertPosition);
}