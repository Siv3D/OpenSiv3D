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

cbuffer GameOfLife : register(b1)
{
	float2 g_pixelSize;
}
// [C++]
//struct GameOfLife
//{
//	Float2 pixelSize;
//};

static const float2 offsets[8] =
{
       float2(-1, -1),
       float2(0, -1),
       float2(1, -1),
       float2(-1, 0),
       float2(1, 0),
       float2(-1, 1),
       float2(0, 1),
       float2(1, 1),
};

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float c = g_texture0.Sample(g_sampler0, input.uv).r;
	
	float n = 0;

	for (uint i = 0; i < 8; ++i)
	{
		n += g_texture0.Sample(g_sampler0, input.uv + offsets[i] * g_pixelSize).r;
	}

	if ((c == 0 && n == 3) || (c == 1 && (n == 2 || n == 3)))
	{
		return float4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		return float4(0.0, 0.0, 0.0, 1.0);
	}
}
