#version 420 core

// BASIC TES

layout(triangles, fractional_odd_spacing, ccw) in;

in vec4 tc_Color[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 v_Color;
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void)
{
	v_Color = tc_Color[0] * gl_TessCoord.x
			+ tc_Color[1] * gl_TessCoord.y
			+ tc_Color[2] * gl_TessCoord.z;

	outData.camPos = inData[0].camPos;

	outData.texCoord = interpolate2D(inData[0].texCoord, inData[1].texCoord, inData[2].texCoord);
	outData.normal = interpolate3D(inData[0].normal, inData[1].normal, inData[2].normal);


	vec4 a = gl_in[0].gl_Position * gl_TessCoord.x;
	vec4 b = gl_in[1].gl_Position * gl_TessCoord.y;
	vec4 c = gl_in[2].gl_Position * gl_TessCoord.z;

	vec4 position = a + b + c;
	outData.position = position;
	gl_Position = position;
}

// PHONG TES
/*
layout(triangles, fractional_odd_spacing, ccw) in;

struct PhongPatch
{
	float termIJ;
	float termJK;
	float termIK;
};


in vec4 tc_Color[];
in mat4 i_ProjMat[];
in PhongPatch i_PhongPatch[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 v_Color;
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

#define Pi  gl_in[0].gl_Position
#define Pj  gl_in[1].gl_Position
#define Pk  gl_in[2].gl_Position

void main(void)
{
	vec3 tc2 = gl_TessCoord * gl_TessCoord;

	outData.texCoord = gl_TessCoord[0]*inData[0].texCoord
					+ gl_TessCoord[1]*inData[1].texCoord
					+ gl_TessCoord[2]*inData[2].texCoord;

	outData.normal = gl_TessCoord[0]*inData[0].normal
					+ gl_TessCoord[1]*inData[1].normal
					+ gl_TessCoord[2]*inData[2].normal;

	v_Color = tc_Color[0] * gl_TessCoord.x
		+ tc_Color[1] * gl_TessCoord.y
		+ tc_Color[2] * gl_TessCoord.z;

	vec4 barPos = gl_TessCoord[0]*Pi
				+ gl_TessCoord[1]*Pj
				+ gl_TessCoord[2]*Pk;

	vec4 termIJ = vec4(i_PhongPatch[0].termIJ, i_PhongPatch[1].termIJ, i_PhongPatch[2].termIJ, 0.0);
	vec4 termJK = vec4(i_PhongPatch[0].termJK, i_PhongPatch[1].termJK, i_PhongPatch[2].termJK, 0.0);
	vec4 termIK = vec4(i_PhongPatch[0].termIK, i_PhongPatch[1].termIK, i_PhongPatch[2].termIK, 0.0);

	vec4 phongPos = tc2[0]*Pi
					+ tc2[1]*Pj
					+ tc2[2]*Pk
					+ gl_TessCoord[0]*gl_TessCoord[1]*termIJ
					+ gl_TessCoord[1]*gl_TessCoord[2]*termJK
					+ gl_TessCoord[2]*gl_TessCoord[0]*termIK;

	vec4 position = (1.0 - 1.0) * barPos + 1.0 * phongPos;
	outData.position = position;
	gl_Position = position;
}*/

// PN TES
/*
layout(triangles, fractional_odd_spacing, ccw) in;

struct PnPatch
{
	float b210;
	float b120;
	float b021;
	float b012;
	float b102;
	float b201;
	float b111;
	float n110;
	float n011;
	float n101;
};

in vec4 tc_Color[];
in PnPatch iPnPatch[];
in mat4 i_ProjMat[];
in vec2 i_TexCoord[];
in vec3 i_Normal[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 v_Color;
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData;

#define b300    gl_in[0].gl_Position
#define b030    gl_in[1].gl_Position
#define b003    gl_in[2].gl_Position
#define n200    i_Normal[0]
#define n020    i_Normal[1]
#define n002    i_Normal[2]
#define uvw     gl_TessCoord

void main()
{
	vec3 uvwSquared = uvw*uvw;
	vec3 uvwCubed   = uvwSquared*uvw;

	// extract control points
	vec4 b210 = vec4(iPnPatch[0].b210, iPnPatch[1].b210, iPnPatch[2].b210, 1.0);
	vec4 b120 = vec4(iPnPatch[0].b120, iPnPatch[1].b120, iPnPatch[2].b120, 1.0);
	vec4 b021 = vec4(iPnPatch[0].b021, iPnPatch[1].b021, iPnPatch[2].b021, 1.0);
	vec4 b012 = vec4(iPnPatch[0].b012, iPnPatch[1].b012, iPnPatch[2].b012, 1.0);
	vec4 b102 = vec4(iPnPatch[0].b102, iPnPatch[1].b102, iPnPatch[2].b102, 1.0);
	vec4 b201 = vec4(iPnPatch[0].b201, iPnPatch[1].b201, iPnPatch[2].b201, 1.0);
	vec4 b111 = vec4(iPnPatch[0].b111, iPnPatch[1].b111, iPnPatch[2].b111, 1.0);

	// extract control normals
	vec4 n110 = normalize(vec4(iPnPatch[0].n110,
							   iPnPatch[1].n110,
							   iPnPatch[2].n110, 1.0));
	vec4 n011 = normalize(vec4(iPnPatch[0].n011,
							   iPnPatch[1].n011,
						       iPnPatch[2].n011, 1.0));
	vec4 n101 = normalize(vec4(iPnPatch[0].n101,
					           iPnPatch[1].n101,
				               iPnPatch[2].n101, 1.0));

	// compute texcoords
	outData.texCoord  = gl_TessCoord[2]*i_TexCoord[0]
	           + gl_TessCoord[0]*i_TexCoord[1]
	           + gl_TessCoord[1]*i_TexCoord[2];

	// normal
	vec3 barNormal = gl_TessCoord[2]*i_Normal[0]
	               + gl_TessCoord[0]*i_Normal[1]
	               + gl_TessCoord[1]*i_Normal[2];
	vec3 pnNormal  = n200*uvwSquared[2]
	               + n020*uvwSquared[0]
	               + n002*uvwSquared[1]
	               + n110.xyz*uvw[2]*uvw[0]
	               + n011.xyz*uvw[0]*uvw[1]
	               + n101.xyz*uvw[2]*uvw[1];
	outData.normal = 1.0*pnNormal + (1.0-1.0)*barNormal; // should we normalize ?

	// compute interpolated pos
	vec4 barPos = gl_TessCoord[2]*b300
	            + gl_TessCoord[0]*b030
	            + gl_TessCoord[1]*b003;

	// save some computations
	uvwSquared *= 3.0;

	// compute PN position
	vec4 pnPos  = b300*uvwCubed[2]
	            + b030*uvwCubed[0]
	            + b003*uvwCubed[1]
	            + b210*uvwSquared[2]*uvw[0]
	            + b120*uvwSquared[0]*uvw[2]
	            + b201*uvwSquared[2]*uvw[1]
	            + b021*uvwSquared[0]*uvw[1]
	            + b102*uvwSquared[1]*uvw[2]
	            + b012*uvwSquared[1]*uvw[0]
	            + b111*6.0*uvw[0]*uvw[1]*uvw[2];

	// final position and normal

	v_Color = tc_Color[0] * gl_TessCoord.x
		+ tc_Color[1] * gl_TessCoord.y
		+ tc_Color[2] * gl_TessCoord.z;

	vec4 finalPos = (1.0-0.0)*barPos + 0.0* pnPos;
	outData.position = finalPos;
	gl_Position = finalPos;
}*/