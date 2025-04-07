//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
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

//
//	Functions
//
float3 ApplySRGBCurve_Fast(float3 color)
{
	return pow(color, (1.0f / 2.2f));
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float3 texColor = g_texture0.Sample(g_sampler0, input.uv).rgb;

	const float brightness = dot(texColor, float3(0.2126f, 0.7152f, 0.0722f));

	if (0.25f < brightness)
	{
		return float4(ApplySRGBCurve_Fast(abs(texColor)) * 0.25f, 1.0f);
	}
	else
	{
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
