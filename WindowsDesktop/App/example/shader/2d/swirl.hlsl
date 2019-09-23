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
//	Float3 _unused = {];
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

float4 PS(VS_OUTPUT input) : SV_Target
{
	const float2 uv = input.tex - float2(0.5, 0.5);

	const float distanceFromCenter = length(uv);

	const float angle = distanceFromCenter * g_angle;

	const float c = cos(angle), s = sin(angle);

	input.tex = mul(uv, float2x2(c, -s, s, c)) + float2(0.5, 0.5);

	return OutputColor(texture0.Sample(sampler0, input.tex) * input.color);
}
