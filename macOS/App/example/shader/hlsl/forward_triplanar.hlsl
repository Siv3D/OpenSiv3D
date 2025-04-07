//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
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
	float3 g_globalAmbientColor;
	float3 g_sunColor;
	float3 g_sunDirection;
}

cbuffer PSPerView : register(b1)
{
	float3 g_eyePosition;
}

cbuffer PSPerMaterial : register(b3)
{
	float3 g_ambientColor;
	uint   g_hasTexture;
	float4 g_diffuseColor;
	float3 g_specularColor;
	float  g_shininess;
	float3 g_emissionColor;
}

//
//	Functions
//
float4 Triplanar(float3 worldPos, float3 normal, float uvScale)
{
	float4 diffuseColor = g_diffuseColor;

	if (g_hasTexture)
	{
		float3 blend = abs(normal);
		blend /= (blend.x + blend.y + blend.z);
		
		worldPos *= uvScale;
		const float4 c0 = g_texture0.Sample(g_sampler0, worldPos.yz);
		const float4 c1 = g_texture0.Sample(g_sampler0, worldPos.xz);
		const float4 c2 = g_texture0.Sample(g_sampler0, worldPos.xy);

		diffuseColor *= (c0 * blend.x + c1 * blend.y + c2 * blend.z);
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
	const float4 diffuseColor = Triplanar(input.worldPosition, n, 0.125f);
	const float3 ambientColor = (g_ambientColor * g_globalAmbientColor);

	// Diffuse
	const float3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	const float3 v = normalize(g_eyePosition - input.worldPosition);
	const float3 h = normalize(v + lightDirection);
	const float3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	return float4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
}
