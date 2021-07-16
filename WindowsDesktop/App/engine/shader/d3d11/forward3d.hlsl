//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		float4 color : TEXCOORD1;
		float2 uv : TEXCOORD2;
		float3 normal : TEXCOORD3;
	};
}

//
//	Constant Buffer
//
cbuffer VSConstants3D : register(b0)
{
	row_major float4x4 g_localToWorld;
	row_major float4x4 g_worldToProjected;
}

cbuffer PSConstants3D : register(b0)
{
	float4 g_diffuseColor: packoffset(c0);
	float3 g_eyePosition : packoffset(c1);
}

//
//	Functions
//
s3d::PSInput VS(s3d::VSInput input)
{
	s3d::PSInput result;

	const float4 worldPosition = mul(input.position, g_localToWorld);

	result.position			= mul(worldPosition, g_worldToProjected);
	result.worldPosition	= worldPosition.xyz;
	result.color			= float4(1.0, 1.0, 1.0, 1.0);
	result.uv				= input.uv;
	result.normal			= mul(input.normal, (float3x3)g_localToWorld);
	return result;
}

float4 PS_Shape(s3d::PSInput input) : SV_TARGET
{
	return (input.color * g_diffuseColor);
}

float4 PS_Texture(s3d::PSInput input) : SV_TARGET
{
	const float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

	return (input.color * g_diffuseColor * texColor);
}
