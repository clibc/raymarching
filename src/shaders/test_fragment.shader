#version 330 core

in  vec2 tCoord;
out vec4 color;

void main()
{
    /* tCoord.xxyy */
    color = vec4(tCoord.xxyy);
}
