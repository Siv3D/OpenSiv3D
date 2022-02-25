//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//
//	Textures
//
Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);

namespace s3d
{
	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position : SV_POSITION;
		float3 worldPosition : TEXCOORD0;
		float2 uv : TEXCOORD1;
		float3 normal : TEXCOORD2;
	};
}

//
//	Constant Buffer
//
cbuffer PSPerFrame : register(b0)
{
	float3 g_gloablAmbientColor;
	float3 g_sunColor;
	float3 g_sunDirection;
}

cbuffer PSPerView : register(b1)
{
	float3 g_eyePosition;
}

cbuffer PSPerMaterial : register(b3)
{
	float3 g_amibientColor;
	uint   g_hasTexture;
	float4 g_diffuseColor;
	float3 g_specularColor;
	float  g_shininess;
	float3 g_emissionColor;
}

cbuffer PSFog : register(b4)
{
	float3 g_fogColor;
	float g_fogCoefficient;
}
// [C++]
//struct PSFog
//{
//	Float3 fogColor;
//	float fogCoefficient;
//};

//
//	Functions
//
float4 GetDiffuseColor(float2 uv)
{
	float4 diffuseColor = g_diffuseColor;

	if (g_hasTexture)
	{
		diffuseColor *= g_texture0.Sample(g_sampler0, uv);
	}

	return diffuseColor;
}

float3 CalculateDiffuseReflection(float3 n, float3 l, float3 lightColor, float3 diffuseColor, float3 ambientColor)
{
	const float3 directColor = lightColor * saturate(dot(n, l));
	return ((ambientColor + directColor) * diffuseColor);
}

float3 CalculateSpecularReflection(float3 n, float3 h, float shininess, float nl, float3 lightColor, float3 specularColor)
{
	const float highlight = pow(saturate(dot(n, h)), shininess) * float(0.0 < nl);
	return (lightColor * specularColor * highlight);
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float3 lightColor		= g_sunColor;
	const float3 lightDirection	= g_sunDirection;

	const float3 n = normalize(input.normal);
	const float3 l = lightDirection;
	const float4 diffuseColor = GetDiffuseColor(input.uv);
	const float3 ambientColor = (g_amibientColor * g_gloablAmbientColor);

	// Diffuse
	const float3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	const float3 v = normalize(g_eyePosition - input.worldPosition);
	const float3 h = normalize(v + lightDirection);
	const float3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	// Exponential Fog
	float4 surfaceColor = float4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
	const float fogFactor = exp(-g_fogCoefficient * distance(g_eyePosition, input.worldPosition));
	surfaceColor.rgb = lerp(g_fogColor, surfaceColor.rgb, fogFactor);

	return surfaceColor;
}
