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

cbuffer PoissonDisk : register(b1)
{
	float2 g_pixelSize;
	float2 g_direction;
}
// [C++]
//struct GaussianBlur
//{
//	Float2 pixelSize;
//	Float2 direction;
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
	const float2 offset1 = 1.3846153846 * g_direction;
	const float2 offset2 = 3.2307692308 * g_direction;

	float4 color = texture0.Sample(sampler0, input.tex) * 0.2270270270;
	color += texture0.Sample(sampler0, input.tex + (offset1 * g_pixelSize)) * 0.3162162162;
	color += texture0.Sample(sampler0, input.tex - (offset1 * g_pixelSize)) * 0.3162162162;
	color += texture0.Sample(sampler0, input.tex + (offset2 * g_pixelSize)) * 0.0702702703;
	color += texture0.Sample(sampler0, input.tex - (offset2 * g_pixelSize)) * 0.0702702703;

	return color;
}
