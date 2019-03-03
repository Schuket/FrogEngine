#version 430

// "domaines" d'evaluation supportees par la tessellation
//							isolines, triangles et quads

// "spacing" = espacement entre les nouveaux vertex generes par la tessellation
// equal_spaceing indique un espacement regulier

layout(quads, equal_spacing) in;
in vec4 tc_Color[];
out vec4 v_Color;

void main(void)
{
	// gl_TessCoord (vec3) poids compris entre [0.0;1.0]

	v_Color = tc_Color[0] * gl_TessCoord.x
			+ tc_Color[1] * gl_TessCoord.y
			+ tc_Color[2] * gl_TessCoord.z;

	vec4 a = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	vec4 b = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
	gl_Position = mix(a, b, gl_TessCoord.y);
}