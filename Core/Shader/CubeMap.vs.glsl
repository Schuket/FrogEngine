#version 420 core

layout (location = 0) in vec3 position;

layout(std140, binding = 1) uniform Matrix
{
    mat4 proj;
	mat4 view;

} inMatrix;  

out vec3 TexCoords;

void main(void)
{
	vec4 pos = inMatrix.proj * mat4(mat3(inMatrix.view)) * vec4(position, 1.0);

	gl_Position = pos.xyww;
	TexCoords = position;
}