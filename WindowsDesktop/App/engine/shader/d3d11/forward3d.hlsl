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
//Texture2D		g_texture0 : register(t0);
//SamplerState	g_sampler0 : register(s0);

namespace s3d
{
	//
	//	VS Input
	//
	struct VSInput
	{
		float4 position : POSITION;
		float3 normal : NORMAL;
		float4 tangent : TANGENT0;
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
		float4 tangent : TEXCOORD3;
		float3 normal : TEXCOORD4;
	};
}

//
//	Constant Buffer
//
cbuffer VSConstants3D : register(b0)
{
	row_major float4x4 g_localToWorld;
	row_major float4x4 g_worldToProjected;
	float4 g_diffuse;
}

cbuffer PSConstants3D : register(b0)
{
	float4 g_placeholderPS;
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
	result.color			= g_diffuse;
	result.uv				= input.uv;
	result.tangent			= input.tangent;
	result.normal			= mul(input.normal, (float3x3)g_localToWorld);
	return result;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float4 color = input.color;
	//color.rgb = input.worldPosition.xyz / 10;

	return color;
}
