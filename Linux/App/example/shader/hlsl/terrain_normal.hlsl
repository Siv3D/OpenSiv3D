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

float2 PS(s3d::PSInput input) : SV_TARGET
{
	float2 size; g_texture0.GetDimensions(size.x, size.y);
	const float2 offset = float2(1.0f, 1.0f) / size;

	const float n = g_texture0.Sample(g_sampler0, input.uv + float2(0, -offset.y)).r;
	const float s = g_texture0.Sample(g_sampler0, input.uv + float2(0,  offset.y)).r;
	const float w = g_texture0.Sample(g_sampler0, input.uv + float2(-offset.x, 0)).r;
	const float e = g_texture0.Sample(g_sampler0, input.uv + float2( offset.x, 0)).r;

	const float3 normal = normalize(float3(w - e, 2.0f, s - n));

	return normal.xz;
}
