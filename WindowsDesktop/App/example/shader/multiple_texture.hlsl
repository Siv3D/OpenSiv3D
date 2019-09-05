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
Texture2D		texture1 : register(t1);
SamplerState	sampler0 : register(s0);
SamplerState	sampler1 : register(s1);

cbuffer PSConstants2D : register(b1)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
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
	float4 texColor = texture0.Sample(sampler0, input.tex);
	texColor.a *= texture1.Sample(sampler1, input.tex).a;

	return OutputColor(texColor * input.color);
}
