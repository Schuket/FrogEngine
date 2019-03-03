
#version 420 core

layout(location = 0) in vec4 a_Position;

layout(std140, binding = 1) uniform Matrix
{
    mat4 proj;
	mat4 view;

} inMatrix;  

void main() 
{	
	gl_Position = inMatrix.proj * inMatrix.view * vec4(a_Position.xyz, 1.0);
}