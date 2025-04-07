//	Copyright (c) 2008-2025 Ryo Suzuki.
//	Copyright (c) 2016-2025 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
layout(location = 0) in vec3 WorldPosition;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Normal;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSPerFrame // slot 0
{
	vec3 g_globalAmbientColor;
	vec3 g_sunColor;
	vec3 g_sunDirection;
};

layout(std140) uniform PSPerView // slot 1
{
	vec3 g_eyePosition;
};

layout(std140) uniform PSPerMaterial // slot 3
{
	vec3  g_ambientColor;
	uint  g_hasTexture;
	vec4  g_diffuseColor;
	vec3  g_specularColor;
	float g_shininess;
	vec3  g_emissionColor;
};

//
//	Functions
//
vec4 GetDiffuseColor(vec2 uv)
{
	vec4 diffuseColor = g_diffuseColor;

	if (g_hasTexture == 1)
	{
		diffuseColor *= texture(Texture0, uv);
	}

	return diffuseColor;
}

vec3 CalculateDiffuseReflection(vec3 n, vec3 l, vec3 lightColor, vec3 diffuseColor, vec3 ambientColor)
{
	vec3 directColor = lightColor * max(dot(n, l), 0.0f);
	return ((ambientColor + directColor) * diffuseColor);
}

vec3 CalculateSpecularReflection(vec3 n, vec3 h, float shininess, float nl, vec3 lightColor, vec3 specularColor)
{
	float highlight = pow(max(dot(n, h), 0.0f), shininess) * float(0.0f < nl);
	return (lightColor * specularColor * highlight);
}

////////////////////////////////////////////////////////////
//
//	Shading
//

uniform sampler2D Texture1;

layout(std140) uniform PSShadow // slot 4
{
	mat4x4 g_worldToProjectedShadow;
	vec3 g_sunPosition;
	float g_lightBleedingReduction;
};

float LineStep(float min, float max, float value)
{
	return clamp((value - min) / (max - min), 0.0, 1.0);
}

float ReduceLightBleeding(float p_max, float amount)
{
	return LineStep(amount, 1.0, p_max);
}

float CalculateShadow(vec3 worldPosition)
{
	vec4 projectedPosition = (vec4(worldPosition, 1.0) * g_worldToProjectedShadow);

	if (any(notEqual(clamp(projectedPosition.xyz, 0.0, 1.0), projectedPosition.xyz)))
	{
		return 1.0;
	}
	
	vec2 uv = vec2(projectedPosition.x, (1.0 - projectedPosition.y));
	float depth = (length(g_sunPosition - worldPosition) - 0.03125);
	vec2 moments = texture(Texture1, uv).rg;

	if (depth <= moments.x)
	{
		return 1.0;
	}

	float variance = (moments.y - (moments.x * moments.x));
	float d = (moments.x - depth);
	float lit = (variance / (variance + (d * d)));

	return ReduceLightBleeding(lit, g_lightBleedingReduction);
}

void main()
{
	// Shadow
	float lit = CalculateShadow(WorldPosition);

	vec3 lightColor		= (g_sunColor * lit);
	vec3 lightDirection	= g_sunDirection;

	vec3 n = normalize(Normal);
	vec3 l = lightDirection;
	vec4 diffuseColor = GetDiffuseColor(UV);
	vec3 ambientColor = (g_ambientColor * g_globalAmbientColor);

	// Diffuse
	vec3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	vec3 v = normalize(g_eyePosition - WorldPosition);
	vec3 h = normalize(v + lightDirection);
	vec3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	FragColor = vec4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
}

//
////////////////////////////////////////////////////////////
