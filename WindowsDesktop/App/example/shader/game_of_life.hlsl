//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

Texture2D		texture0 : register(t0);
SamplerState	sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
}

cbuffer GameOfLife : register(b1)
{
	float2 g_pixelSize;
}
// [C++]
//struct GameOfLife
//{
//	Float2 pixelSize;
//	Float2 _unused = {};
//};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 tex		: TEXCOORD0;
	float4 color	: COLOR0;
};

float4 OutputColor(const float4 color)
{
	return color + g_colorAdd;
}

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

float4 PS(VS_OUTPUT input) : SV_Target
{
	const float c = texture0.Sample(sampler0, input.tex).r;
	float n = 0;

	for (int i = 0; i < 8; ++i)
	{
		n += texture0.Sample(sampler0, input.tex + offsets[i] * g_pixelSize).r;
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
