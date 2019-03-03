#version 420 core

in VData
{
    vec4 position;
    vec3 normal;
    vec2 texCoord;
    vec4 camPos;
	vec3 tangent;
} inData[];

out FData
{
    vec4 position;
    vec3 normal;
    vec2 texCoord;
    vec4 camPos;
	vec3 tangent;
} outData;

layout(triangles) in;
//layout(points, max_vertices = 3) out;
//layout(line_strip, max_vertices = 3) out;
layout(triangle_strip, max_vertices = 3) out;

void main()
{

	for (int i = 0; i < gl_in.length; i++)
	{
		outData.position = inData[i].position;
		outData.normal = inData[i].normal;
		outData.texCoord = inData[i].texCoord;
		outData.camPos = inData[i].camPos;
		outData.tangent = inData[i].tangent;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
}