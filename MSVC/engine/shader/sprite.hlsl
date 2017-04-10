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

float4 PS(VS_OUTPUT input) : SV_Target
{
	return texture0.Sample(sampler0, input.tex) * input.color;
}
