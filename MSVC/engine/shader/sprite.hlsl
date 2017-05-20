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

Texture2D		texture0 : register(t0);
SamplerState	sampler0 : register(s0);

cbuffer vscbSprite : register(b0)
{
	row_major float2x4 g_transform;
}

struct VS_INPUT
{
	float2 position	: POSITION;
	float2 tex		: TEXCOORD0;
	float4 color	: COLOR0;
};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 tex		: TEXCOORD0;
	float4 color	: COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position.xy	= g_transform._13_14 + input.position.x * g_transform._11_12 + input.position.y * g_transform._21_22;
	output.position.z	= g_transform._23;
	output.position.w	= g_transform._24;
	output.tex			= input.tex;
	output.color		= input.color;

	return output;
}

float4 PS_Shape(VS_OUTPUT input) : SV_Target
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

float4 PS_Sprite(VS_OUTPUT input) : SV_Target
{
	return texture0.Sample(sampler0, input.tex) * input.color;
}

float4 PS_SDF(VS_OUTPUT input) : SV_Target
{
	float a = texture0.Sample(sampler0, input.tex).a;

	const float MIN_EDGE_VALUE = 0.48;
	
	const float MAX_EDGE_VALUE = 0.52;

	if (a < MIN_EDGE_VALUE)
	{
		a = 0.0;
	}
	else if (MAX_EDGE_VALUE < a)
	{
		a = 1.0;
	}
	else
	{
		a = smoothstep(MIN_EDGE_VALUE, MAX_EDGE_VALUE, a);
	}

	return float4(input.color.rgb, input.color.a * a);
}
