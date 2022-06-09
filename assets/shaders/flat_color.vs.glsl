#version 330 core

layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;

out _vs_out
{
  vec4 color;
} vs_out;

uniform mat4 u_view_projection;
uniform mat4 u_model;

void main()
{
  const vec4 vertices[3] = vec4[3] (vec4(0.25, -0.25, 0.5, 1.0),
                                   vec4(-0.25, -0.25, 0.5, 1.0),
                                   vec4(0.25, 0.25, 0.5, 1.0));

  gl_Position = vertices[gl_VertexID] + offset;

  vs_out.color = color;
};
