//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//
//	Textures
//
Texture2D g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

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
	uint g_hasTexture;
	float4 g_diffuseColor;
	float3 g_specularColor;
	float g_shininess;
	float3 g_emissionColor;
}

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

////////////////////////////////////////////////////////////
//
//	Depth
//
cbuffer PSShadow : register(b4)
{
	row_major float4x4 g_worldToProjectedShadow;
	float3 g_sunPosition;
	float g_lightBleedingReduction;
}

float2 Depth_PS(s3d::PSInput input) : SV_TARGET
{
	const float depth = length(g_sunPosition - input.worldPosition);
	return float2(depth, (depth * depth));
}
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
//	Shading
//
Texture2D g_texture1 : register(t1);
SamplerState g_sampler1 : register(s1);

float LineStep(float min, float max, float value)
{
	return saturate((value - min) / (max - min));
}

float ReduceLightBleeding(float p_max, float amount)
{
	return LineStep(amount, 1.0, p_max);
}

float CalculateShadow(float3 worldPosition)
{
	const float4 projectedPosition = mul(float4(worldPosition, 1.0), g_worldToProjectedShadow);

	if (any(saturate(projectedPosition.xyz) != projectedPosition.xyz))
	{
		return 1.0;
	}
	
	const float2 uv = float2(projectedPosition.x, (1.0 - projectedPosition.y));
	const float depth = (length(g_sunPosition - worldPosition) - 0.03125);
	const float2 moments = g_texture1.Sample(g_sampler1, uv).rg;

	if (depth <= moments.x)
	{
		return 1.0;
	}

	const float variance = (moments.y - (moments.x * moments.x));
	const float d = (moments.x - depth);
	const float lit = (variance / (variance + (d * d)));

	return ReduceLightBleeding(lit, g_lightBleedingReduction);
}

float4 Shading_PS(s3d::PSInput input) : SV_TARGET
{
	// Shadow
	const float lit = CalculateShadow(input.worldPosition);

	const float3 lightColor = (g_sunColor * lit);
	const float3 lightDirection = g_sunDirection;

	const float3 n = normalize(input.normal);
	const float3 l = lightDirection;
	float4 diffuseColor = GetDiffuseColor(input.uv);
	const float3 ambientColor = (g_ambientColor * g_globalAmbientColor);

	// Diffuse
	const float3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	const float3 v = normalize(g_eyePosition - input.worldPosition);
	const float3 h = normalize(v + lightDirection);
	const float3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	return float4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
}
//
////////////////////////////////////////////////////////////
