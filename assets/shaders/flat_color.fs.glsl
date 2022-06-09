#version 330 core

in _vs_out
{
  vec4 color;
} fs_in;

out vec4 color;

void main()
{
    color = fs_in.color;
};
