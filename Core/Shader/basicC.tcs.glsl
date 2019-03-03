#version 430

// Le nombre de points en entree est stockee dans gl_PatchVerticesIn (int)

layout(vertices = 4) out;

in vec4 v_Color[];
out vec4 tc_Color[];

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
}