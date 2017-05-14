//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 tex		: TEXCOORD0;
	float4 color	: COLOR0;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}

float4 PS_LineDot(VS_OUTPUT input) : SV_Target
{
	const float t = min(abs(1.5 - fmod(input.tex.x, 3.0)) * 1.7, 1.0);

	input.color.a *= pow(t, 24);

	return input.color;
}

float4 PS_LineRoundDot(VS_OUTPUT input) : SV_Target
{
	const float t = fmod(input.tex.x, 2.0);

	input.tex.x = abs(1 - t) * 2.0;

	input.color.a *= 1.0 - saturate(pow(dot(input.tex, input.tex), 12));

	return input.color;
}
