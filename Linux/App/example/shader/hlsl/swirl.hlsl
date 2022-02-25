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
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};
}

//
//	Constant Buffer
//
cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

cbuffer Swirl : register(b1)
{
	float  g_angle;
}
// [C++]
//struct Swirl
//{
//	float angle;
//};

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float2 uv = input.uv - float2(0.5, 0.5);
	float distanceFromCenter = length(uv);
	float angle = distanceFromCenter * g_angle;
	float c = cos(angle), s = sin(angle);

	uv = mul(uv, float2x2(c, -s, s, c)) + float2(0.5, 0.5);

	float4 texColor = g_texture0.Sample(g_sampler0, uv);

	return (texColor * input.color) + g_colorAdd;
}
