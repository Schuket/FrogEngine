#version 420 core

in VData
{
	vec3 scale;
	float radius;
} inData[];

layout(points) in;
layout(line_strip, max_vertices = 6) out;

void main(void)
{
	vec4 newRadiusX = vec4(inData[0].radius * inData[0].scale.x, 0.0, 0.0, 0.0);
	vec4 newRadiusY = vec4(0.0, inData[0].radius * inData[0].scale.y, 0.0, 0.0);
	vec4 newRadiusZ = vec4(0.0, 0.0, inData[0].radius * inData[0].scale.z, 0.0);

	gl_Position = gl_in[0].gl_Position + newRadiusY;
	EmitVertex(); 
				  
	gl_Position = gl_in[0].gl_Position - newRadiusY;
	EmitVertex(); 
		
	EndPrimitive();
	
	gl_Position = gl_in[0].gl_Position + newRadiusX;
	EmitVertex(); 
				  
	gl_Position = gl_in[0].gl_Position - newRadiusX;
	EmitVertex();
	
	EndPrimitive();
	
	gl_Position = gl_in[0].gl_Position + newRadiusZ;
	EmitVertex(); 
				  
	gl_Position = gl_in[0].gl_Position - newRadiusZ;
	EmitVertex();
	
	EndPrimitive();
}