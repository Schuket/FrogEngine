#version 420 core

in vec3 TexCoords;
uniform samplerCube skybox;

out vec4 Color;

void main(void)
{
    Color = texture(skybox, TexCoords);
}