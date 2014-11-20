uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normal;

varying vec4 fragPosition;
varying vec4 fragNormal;
varying vec2 fragUv;

void main()
{
	vec3 color = vec3(0.0, 1.0, 0.0);
	gl_FragColor = vec4(color, 1.0);
}