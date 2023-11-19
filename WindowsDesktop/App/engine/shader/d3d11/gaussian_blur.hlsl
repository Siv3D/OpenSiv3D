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

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float2 g_pixelSize;
	float2 g_direction;
}

float4 Blur5_PS(s3d::PSInput input) : SV_TARGET
{
    const float2 offset1 = (1.33333333333333 * g_direction);
	
    float4 result = (g_texture0.Sample(g_sampler0, input.uv) * 0.294117647058824);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset1 * g_pixelSize)) * 0.352941176470588);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset1 * g_pixelSize)) * 0.352941176470588);
	
    return result;
}

float4 Blur9_PS(s3d::PSInput input) : SV_TARGET
{
    const float2 offset1 = (1.38461538461538 * g_direction);
    const float2 offset2 = (3.23076923076923 * g_direction);

    float4 result = (g_texture0.Sample(g_sampler0, input.uv) * 0.227027027027027);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset1 * g_pixelSize)) * 0.316216216216216);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset1 * g_pixelSize)) * 0.316216216216216);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset2 * g_pixelSize)) * 0.070270270270270);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset2 * g_pixelSize)) * 0.070270270270270);

	return result;
}

float4 Blur13_PS(s3d::PSInput input) : SV_TARGET
{
    const float2 offset1 = (1.41176470588235 * g_direction);
    const float2 offset2 = (3.29411764705882 * g_direction);
    const float2 offset3 = (5.17647058823529 * g_direction);
	
    float4 result = (g_texture0.Sample(g_sampler0, input.uv) * 0.196482550151140);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset1 * g_pixelSize)) * 0.296906964672834);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset1 * g_pixelSize)) * 0.296906964672834);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset2 * g_pixelSize)) * 0.0944703978504473);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset2 * g_pixelSize)) * 0.0944703978504473);
    result += (g_texture0.Sample(g_sampler0, input.uv + (offset3 * g_pixelSize)) * 0.0103813624011481);
    result += (g_texture0.Sample(g_sampler0, input.uv - (offset3 * g_pixelSize)) * 0.0103813624011481);
    
    return result;
}
