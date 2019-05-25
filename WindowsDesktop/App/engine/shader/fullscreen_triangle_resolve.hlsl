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

Texture2DMS<float4, 4> texture0 : register(t0);

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 result = texture0.Load(input.tex.xy, 0).rgb;
	result += texture0.Load(input.tex.xy, 1).rgb;
	result += texture0.Load(input.tex.xy, 2).rgb;
	result += texture0.Load(input.tex.xy, 3).rgb;
	return float4(result / 4, 1);
}
