#version 420 core

#define MAX_LIGHT 10

//enum
#define POSITION  1
#define DIRECTIONAL 2
#define SPOT 3
#define AMBIANT 4

out vec4 outColor;
uniform sampler2D Sampler;

in FData
{
    vec4 position;
    vec3 normal;
    vec2 texCoord;
    vec4 camPos;

} inFData;

struct light
{
    vec4 position;
    vec4 direction;
    vec4 color;
    float intensity;
    float ambientCoeff;
    float fov;
    int ID;
};

layout(std140, binding = 2) uniform Light
{
    light inLight[MAX_LIGHT];
	int lightNb;

};

layout(std140, binding = 3) uniform Material
{
	vec4 transmissFilter;
	vec4 ambiant;
	vec4 diffuse;
	vec4 specular;
	vec4 emissive;
	
	float shiningness;
	float refractionAngle;
	float alphaCoeff;
	float alphaInverse;
	
	int illum;

} inMtl;


        // ~~~~ //

vec3 FindLightDirection(light inLight)
{
    if (inLight.ID == DIRECTIONAL)
		return vec3(normalize(vec3(inLight.direction)));
    
    else 
	   return -vec3(normalize(inLight.position - inFData.position));    
}

        // ~~~~ //

float DiffuseCoeff(vec3 lightDir)
{
    float Angle = dot(-lightDir, inFData.normal); 
    
    return  max(Angle, 0.0); 
}

        // ~~~~ //

float SpecularCoeff(vec3 lightDir)
{
    vec3 viewDir = vec3(normalize(inFData.camPos - inFData.position));
    vec3 reflectDir = normalize(reflect(normalize(lightDir), inFData.normal));

    float specularCoeff = 0.0;

    if (dot(-lightDir, inFData.normal) > 0.0)
        specularCoeff = pow(max(dot(viewDir, reflectDir), 0.0), inMtl.shiningness);                     
                                
    return specularCoeff;
}

        // ~~~~ //

float CalculateAttenuate(light inLight)
{
    if (inLight.ID == DIRECTIONAL)
        return 1.f;

    else  
    {
        float dist = length(vec3(inLight.position - inFData.position));
        return inLight.intensity /(1.0 * pow(dist, 2)); //(kconst + (klinear * dist) + (kquadra * pow(dist, 2.0))));
    }
}

        // ~~~~ //

void SpotLightRestriction(light inLight, inout float attenuate, vec3 lightDir)
{
    float lightToSurfaceAngle = degrees(acos(dot(lightDir, inLight.direction.xyz)));
    if (lightToSurfaceAngle > inLight.fov / 2.0)
        attenuate = 0.0;   // try to implement attenuation for spotlight
}

        // ~~~~ //          

vec4 ApplyLight(light inLight, vec4 texColor)
{	
	vec4 ambiantColor = inLight.ambientCoeff * inLight.color * inMtl.ambiant * texColor;
	
    if (inLight.ID == AMBIANT)
		return ambiantColor;
		
    vec3 lightDir = FindLightDirection(inLight);

    float diffuseCoeff = DiffuseCoeff(lightDir);
	vec4 diffuseColor = diffuseCoeff * inLight.color * inMtl.diffuse * texColor;
    float specularCoeff = SpecularCoeff(lightDir);
	vec4 specularColor = specularCoeff * inLight.color * inMtl.specular;

    float attenuate = CalculateAttenuate(inLight);

    if (inLight.ID == SPOT)
		SpotLightRestriction(inLight, attenuate, lightDir);

    vec4 linearLight = ambiantColor + (diffuseColor + specularColor) * attenuate;

    return linearLight;
}

        // ~~~~ //

void main(void)
{
    vec4 texColor = texture(Sampler, inFData.texCoord);
	vec4 FinalColor = vec4(0.0, 0.0, 0.0, 0.0);

    for (int idx = 0; idx < lightNb; idx++)
		FinalColor +=  ApplyLight(inLight[idx], texColor) ;

	outColor = FinalColor;
}
