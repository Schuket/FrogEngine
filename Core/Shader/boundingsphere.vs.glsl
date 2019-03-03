#version 420 core

layout(std140, binding = 1) uniform Matrix
{
    mat4 proj;
	mat4 view;
} inMatrix;  

layout(std140, binding = 4) uniform boundingSphere
{
	mat4 worldMatrix;
	vec3 scale;
	float radius;
} inData;

out VData
{
	vec3 scale;
	float radius;
} outData;

			// ~~~~ //

void SetVertexData()
{
    outData.scale = inData.scale;
	outData.radius = inData.radius;
}

	        // ~~~~ //

void main(void)
{		
	SetVertexData();

	gl_Position = inMatrix.proj * inMatrix.view * inData.worldMatrix * vec4(0.0, 0.0, 0.0, 1.0);
}