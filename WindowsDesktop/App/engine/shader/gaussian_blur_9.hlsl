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
	float2 g_pixelSize;
	float2 g_direction;
}

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 tex		: TEXCOORD0;
	float4 color	: COLOR0;
};

//
// http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
//
float4 PS(VS_OUTPUT input) : SV_Target
{
	const float2 offset1 = 1.38461538461538 * g_direction;
	const float2 offset2 = 3.23076923076923 * g_direction;

	float4 color = texture0.Sample(sampler0, input.tex) * 0.227027027027027;
	color += texture0.Sample(sampler0, input.tex + (offset1 * g_pixelSize)) * 0.316216216216216;
	color += texture0.Sample(sampler0, input.tex - (offset1 * g_pixelSize)) * 0.316216216216216;
	color += texture0.Sample(sampler0, input.tex + (offset2 * g_pixelSize)) * 0.070270270270270;
	color += texture0.Sample(sampler0, input.tex - (offset2 * g_pixelSize)) * 0.070270270270270;

	return color;
}
