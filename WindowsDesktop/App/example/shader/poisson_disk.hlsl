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
	float  g_diskRadius;
}
// [C++]
//struct PoissonDisk
//{
//	Float2 pixelSize;
//	float diskRadius;
//	float _unused = 0.0f;
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

static const float2 poisson[12] =
{
       float2(-0.326212, -0.405805),
       float2(-0.840144, -0.07358),
       float2(-0.695914, 0.457137),
       float2(-0.203345, 0.620716),
       float2(0.96234, -0.194983),
       float2(0.473434, -0.480026),
       float2(0.519456, 0.767022),
       float2(0.185461, -0.893124),
       float2(0.507431, 0.064425),
       float2(0.89642, 0.412458),
       float2(-0.32194, -0.932615),
       float2(-0.791559, -0.597705)
};

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 accum = texture0.Sample(sampler0, input.tex);

	for (int tap = 0; tap < 12; ++tap)
	{
		float2 texCoord = input.tex + (g_pixelSize * poisson[tap] * g_diskRadius);
		accum.rgb += texture0.Sample(sampler0, texCoord).rgb;
	}

	accum.rgb /= 13.0;

	return OutputColor(accum * input.color);
}
