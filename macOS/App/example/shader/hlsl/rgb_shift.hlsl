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

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float2 ra = g_texture0.Sample(g_sampler0, input.uv + float2(-0.02, 0.0)).ra;
	float2 ga = g_texture0.Sample(g_sampler0, input.uv).ga;
	float2 ba = g_texture0.Sample(g_sampler0, input.uv + float2(0.02, 0.0)).ba;

	float a = (ra.y + ga.y + ba.y) / 3;
	float4 texColor = float4(ra.x, ga.x, ba.x, a);

	return (texColor * input.color) + g_colorAdd;
}
