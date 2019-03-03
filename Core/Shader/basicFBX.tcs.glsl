#version 420 core

// Le nombre de points en entree est stockee dans gl_PatchVerticesIn (int)

// Basic TCS

layout(vertices = 3) out;

in vec4 v_Color[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 tc_Color[];
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData[];

#define ID gl_InvocationID

void main(void)
{
// Subdivision interne
	gl_TessLevelInner[0] = 1.0; // non defini pour les isolines
	gl_TessLevelInner[1] = 1.0; // non defini pour les isolines et triangles

	// Subdivision externe
	gl_TessLevelOuter[0] = 1.0;
	gl_TessLevelOuter[1] = 1.0;
	gl_TessLevelOuter[2] = 1.0; // non defini pour les isolines
	gl_TessLevelOuter[3] = 1.0; // non defini pour les isolines et triangles

	// ecriture des donnees en sortie
	gl_out[ID].gl_Position = gl_in[ID].gl_Position;
	tc_Color[ID] = v_Color[ID];
	outData[ID].position = inData[ID].position;
	outData[ID].normal = inData[ID].normal;
	outData[ID].texCoord = inData[ID].texCoord;
	outData[ID].camPos = inData[ID].camPos;
	outData[ID].position = inData[ID].position;
}

// PHONG TCS
/*
layout(vertices = 3) out;

struct PhongPatch
{
	float termIJ;
	float termJK;
	float termIK;
};

in vec4 v_Color[];
in mat4 i_ProjMat[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 tc_Color[];
out mat4 o_ProjMat[];
out PhongPatch o_PhongPatch[3];
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData[];


#define Pi  gl_in[0].gl_Position.xyz
#define Pj  gl_in[1].gl_Position.xyz
#define Pk  gl_in[2].gl_Position.xyz
#define ID gl_InvocationID

float PIi(int i, vec3 q)
{
	vec3 q_minus_p = q-gl_in[i].gl_Position.xyz;
	return q[ID] - dot(q_minus_p, outData[i].normal) * outData[i].normal[ID];
}

void main(void)
{
	outData[ID].position = inData[ID].position;
	outData[ID].normal = inData[ID].normal;
	outData[ID].texCoord = inData[ID].texCoord;
	outData[ID].camPos = inData[ID].camPos;

	gl_out[ID].gl_Position = gl_in[ID].gl_Position;
	o_ProjMat[ID] = i_ProjMat[ID];
	tc_Color[ID] = v_Color[ID];

	o_PhongPatch[ID].termIJ = PIi(0,Pj) + PIi(1,Pi);
	o_PhongPatch[ID].termJK = PIi(1,Pk) + PIi(2,Pj);
	o_PhongPatch[ID].termIK = PIi(2,Pi) + PIi(0,Pk);

	gl_TessLevelOuter[ID] = 2.0;
	gl_TessLevelInner[0] = 2.0;
}*/

// PN TCS
/*
layout(vertices = 3) out;

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

in vec4 v_Color[];
in mat4 i_ProjMat[];
in vec4 i_Position[];
in vec2 i_TexCoord[];
in vec3 i_Normal[];
in VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} inData[];

out vec4 tc_Color[];
out PnPatch oPnPatch[3];
out mat4 o_ProjMat[];
out vec2 o_TexCoord[3];
out vec3 o_Normal[3];
out VData
{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
	vec4 camPos;

} outData[];

float wij(int i, int j)
{
	return dot(gl_in[j].gl_Position.xyz - gl_in[i].gl_Position.xyz, inData[i].normal);
}

float vij(int i, int j)
{
	vec3 Pj_minus_Pi = gl_in[j].gl_Position.xyz
	                 - gl_in[i].gl_Position.xyz;
	vec3 Ni_plus_Nj  = inData[i].normal+inData[j].normal;
	return 2.0*dot(Pj_minus_Pi, Ni_plus_Nj)/dot(Pj_minus_Pi, Pj_minus_Pi);
}

#define ID gl_InvocationID

void main()
{
	// get data
	gl_out[ID].gl_Position = gl_in[ID].gl_Position;
	outData[ID].position = inData[ID].position;
	outData[ID].normal = inData[ID].normal;
	outData[ID].texCoord = inData[ID].texCoord;
	outData[ID].camPos = inData[ID].camPos;
	
	o_ProjMat[ID] = i_ProjMat[ID];
	o_Normal[ID] = i_Normal[ID];
	o_TexCoord[ID] = i_TexCoord[ID];

	// set base 
	float P0 = gl_in[0].gl_Position[ID];
	float P1 = gl_in[1].gl_Position[ID];
	float P2 = gl_in[2].gl_Position[ID];
	float N0 = i_Normal[0][ID];
	float N1 = i_Normal[1][ID];
	float N2 = i_Normal[2][ID];

	// compute control points (will be evaluated three times ...)
	float b210 = (2.0*P0 + P1 - wij(0,1)*N0)/3.0;
	float b120 = (2.0*P1 + P0 - wij(1,0)*N1)/3.0;
	float b021 = (2.0*P1 + P2 - wij(1,2)*N1)/3.0;
	float b012 = (2.0*P2 + P1 - wij(2,1)*N2)/3.0;
	float b102 = (2.0*P2 + P0 - wij(2,0)*N2)/3.0;
	float b201 = (2.0*P0 + P2 - wij(0,2)*N0)/3.0;

	float E = ( b210
	          + b120
	          + b021
	          + b012
	          + b102
	          + b201 ) / 6.0;
	float V = (P0 + P1 + P2)/3.0;
	oPnPatch[ID].b210 = b210;
	oPnPatch[ID].b120 = b120;
	oPnPatch[ID].b021 = b021;
	oPnPatch[ID].b012 = b012;
	oPnPatch[ID].b102 = b102;
	oPnPatch[ID].b201 = b201;
	oPnPatch[ID].b111 = E + (E - V)*0.5;
	oPnPatch[ID].n110 = N0+N1-vij(0,1)*(P1-P0);
	oPnPatch[ID].n011 = N1+N2-vij(1,2)*(P2-P1);
	oPnPatch[ID].n101 = N2+N0-vij(2,0)*(P0-P2);

	// set tess levels
	gl_TessLevelOuter[ID] = 2.0;
	gl_TessLevelInner[0] = 2.0;
}*/