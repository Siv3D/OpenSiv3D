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

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
	return float4(texture0.Sample(sampler0, input.tex.xy).rgb, 1);
}
