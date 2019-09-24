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
	const float2 ra = texture0.Sample(sampler0, input.tex + float2(-0.02, 0.0)).ra;
	const float2 ga = texture0.Sample(sampler0, input.tex + float2(0.0, 0.0)).ga;
	const float2 ba = texture0.Sample(sampler0, input.tex + float2(0.02, 0.0)).ba;
	const float4 texColor = float4(ra.x, ga.x, ba.x, (ra.y + ga.y + ba.y) / 3);

	return OutputColor(texColor * input.color);
}
