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
	//	VS Input
	//
	struct VSInput
	{
		float2 position	: POSITION;
		float2 uv		: TEXCOORD0;
		float4 color	: COLOR0;
	};

	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};

	//
	//	Siv3D Functions
	//
	float4 Transform2D(float2 pos, float2x4 t)
	{
		return float4((t._13_14 + (pos.x * t._11_12) + (pos.y * t._21_22)), t._23_24);
	}
}

//
//	Constant Buffer
//
cbuffer VSConstants2D : register(b0)
{
	row_major float2x4 g_transform;
	float4 g_colorMul;
}

cbuffer VSHomography : register(b1)
{
	row_major float3x3 g_homography;
}

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

cbuffer PSHomography : register(b1)
{
	row_major float3x3 g_invHomography;
}

//
//	Functions
//
float2 Transform(const float2 pos, const float3x3 mat)
{
	const float s = (mat._13 * pos.x + mat._23 * pos.y + mat._33);
	const float x = (mat._11 * pos.x + mat._21 * pos.y + mat._31) / s;
	const float y = (mat._12 * pos.x + mat._22 * pos.y + mat._32) / s;
	return float2(x, y);
}

s3d::PSInput VS(s3d::VSInput input)
{
	s3d::PSInput result;
	input.position	= Transform(input.position, g_homography);
	result.position	= s3d::Transform2D(input.position, g_transform);
	result.color	= input.color * g_colorMul;
	result.uv		= input.position;
	return result;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float2 uv = Transform(input.uv, g_invHomography);
	const float4 texColor = g_texture0.Sample(g_sampler0, uv);

	return ((texColor * input.color) + g_colorAdd);
}
