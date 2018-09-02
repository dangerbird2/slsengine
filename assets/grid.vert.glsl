
uniform mat4 modelview;
uniform mat4 projection;
layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec4 vert_color;
layout(location = 4) in vec2 vert_uv;
out vec2 frag_uv;
out vec4 frag_color;

void
main()
{
  frag_uv = vert_uv;
  frag_color = vert_color;
  gl_Position = projection * modelview * vec4(vert_pos.xyz, 1.0);
}
