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

float4 OutputColor(const float4 color)
{
	return color + g_colorAdd;
}

//
// http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
//
float4 PS(VS_OUTPUT input) : SV_Target
{
	const float2 offset1 = 1.41176470588235 * g_direction;
	const float2 offset2 = 3.29411764705882 * g_direction;
	const float2 offset3 = 5.17647058823529 * g_direction;

	float4 color = texture0.Sample(sampler0, input.tex) * 0.19648255015114;
	color += texture0.Sample(sampler0, input.tex + (offset1 * g_pixelSize)) * 0.296906964672834;
	color += texture0.Sample(sampler0, input.tex - (offset1 * g_pixelSize)) * 0.296906964672834;
	color += texture0.Sample(sampler0, input.tex + (offset2 * g_pixelSize)) * 0.094470397850447;
	color += texture0.Sample(sampler0, input.tex - (offset2 * g_pixelSize)) * 0.094470397850447;
	color += texture0.Sample(sampler0, input.tex + (offset3 * g_pixelSize)) * 0.010381362401148;
	color += texture0.Sample(sampler0, input.tex - (offset3 * g_pixelSize)) * 0.010381362401148;

	return color;
}
