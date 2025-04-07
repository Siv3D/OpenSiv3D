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
Texture2D		g_texture1 : register(t1);
Texture2D		g_texture2 : register(t2);
SamplerState	g_sampler0 : register(s0);
SamplerState	g_sampler1 : register(s1);
SamplerState	g_sampler2 : register(s2);

namespace s3d
{
	//
	//	VS Input
	//
	struct VSInput
	{
		float4 position : POSITION;
		float3 normal : NORMAL;
		float2 uv : TEXCOORD0;
	};

	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position : SV_POSITION;
		float3 worldPosition : TEXCOORD0;
		float2 uv : TEXCOORD1;
	};
}

//
//	Constant Buffer
//
cbuffer VSPerView : register(b1)
{
	row_major float4x4 g_worldToProjected;
}

cbuffer VSPerObject : register(b2)
{
	row_major float4x4 g_localToWorld;
}

cbuffer VSPerMaterial : register(b3)
{
	float4 g_uvTransform;
}

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
s3d::PSInput VS(s3d::VSInput input)
{
	s3d::PSInput result;

	const float2 uv = (input.uv * g_uvTransform.xy + g_uvTransform.zw);
	const float height = g_texture0.SampleLevel(g_sampler0, uv, 0).r;
	const float4 pos = float4(input.position.x, height, input.position.zw);
	const float4 worldPosition = mul(pos, g_localToWorld);

	result.position			= mul(worldPosition, g_worldToProjected);
	result.worldPosition	= worldPosition.xyz;
	result.uv				= uv;
	return result;
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

float3 FetchNormal(float2 uv)
{
	const float2 m = g_texture1.Sample(g_sampler1, uv).rg;
	return float3(m.x, sqrt(1.0 - m.x * m.x - m.y * m.y), m.y);
}

float4 TerrainTriplanar(float3 worldPos, float3 normal, float uvScale)
{
	float4 diffuseColor = g_diffuseColor;

	if (g_hasTexture)
	{
		normal.y = pow(abs(normal.y), 32.0f); // less grass on slopes

		float3 blend = abs(normal);
		blend /= (blend.x + blend.y + blend.z);

		worldPos *= uvScale;
		const float4 c0 = g_texture2.Sample(g_sampler0, worldPos.yz);
		const float4 c1 = g_texture0.Sample(g_sampler0, worldPos.xz);
		const float4 c2 = g_texture2.Sample(g_sampler0, worldPos.xy);

		diffuseColor *= (c0 * blend.x + c1 * blend.y + c2 * blend.z);
	}

	return diffuseColor;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float3 lightColor		= g_sunColor;
	const float3 lightDirection	= g_sunDirection;

	const float3 n = FetchNormal(input.uv);
	const float3 l = lightDirection;
	const float4 diffuseColor = TerrainTriplanar(input.worldPosition, n, 0.5f);
	const float3 ambientColor = (g_ambientColor * g_globalAmbientColor);

	// Diffuse
	const float3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	const float3 v = normalize(g_eyePosition - input.worldPosition);
	const float3 h = normalize(v + lightDirection);
	const float3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	return float4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
}
