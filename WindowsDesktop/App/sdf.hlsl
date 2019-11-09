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

Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_internal;
}

cbuffer SDFParameters : register(b1)
{
	float g_a;
	float g_b;
	float g_c;
	float g_d;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}

float4 PS(PSInput input) : SV_TARGET
{
	float pxRange = g_a;

	float2 size;
	g_texture0.GetDimensions(size.x, size.y);

	float2 msdfUnit = pxRange / size;

	float4 s = g_texture0.Sample(g_sampler0, input.uv);

	float sigDist = median(s.r, s.g, s.b) - 0.5;

	sigDist *= dot(msdfUnit, 0.5 / fwidth(input.uv));

	float a = saturate(sigDist + 0.5);

	input.color.a *= (a * s.a);

	return input.color + g_colorAdd;
}
