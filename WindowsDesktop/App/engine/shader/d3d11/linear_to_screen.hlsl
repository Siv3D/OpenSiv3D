//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

float3 Gamma(float3 color, float g)
{
	return pow(color, g);
}

float3 PS(s3d::PSInput input) : SV_TARGET
{
	const float3 texColor = g_texture0.Sample(g_sampler0, input.uv).rgb;

	return Gamma(abs(texColor), 1.0 / 2.2);
}
