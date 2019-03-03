#version 420 core

#define MAX_WORLD_MATRIX 100000

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Tangent;

layout(std140, binding = 1) uniform Matrix
{
    mat4 proj;
	mat4 view;

} inMatrix;  

uniform float u_Time;
uniform mat4 worldMatrix;

/*out mat4 o_ProjMat;
out vec4 o_Position;
out vec2 o_TexCoord;
out vec3 o_Normal;*/

out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;
	vec3 tangent;
} outData;

			// ~~~~ //

void SetVertexData()
{
	outData.position = worldMatrix * a_Position;

	mat3 normalMatrix = transpose(inverse(mat3(worldMatrix)));
    outData.normal = normalize(normalMatrix * a_Normal);

	outData.texCoord = a_TexCoord;
	/*Position = a_Position;
	o_TexCoord = a_TexCoord;
	o_Normal = a_Normal;*/
	outData.camPos = inverse(inMatrix.view)[3];
}

	        // ~~~~ //

void main(void)
{		
	SetVertexData();
	//o_ProjMat = inMatrix.proj;

	gl_Position = inMatrix.proj * inMatrix.view * worldMatrix * a_Position;
}