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

cbuffer vscbSprite : register(b0)
{
	row_major float2x4 g_transform;
	float4 g_colorMul;
}

cbuffer pscbSprite : register(b1)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
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

float4 StandardTransform(const float2 pos)
{
	float4 output;
	output.xy	= g_transform._13_14 + pos.x * g_transform._11_12 + pos.y * g_transform._21_22;
	output.z	= g_transform._23;
	output.w	= g_transform._24;
	return output;
}

float4 OutputColor(const float4 color)
{
	return color + g_colorAdd;
}

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position	= StandardTransform(input.position);
	output.tex		= input.tex;
	output.color	= input.color * g_colorMul;
	return output;
}

float4 PS_Shape(VS_OUTPUT input) : SV_Target
{
	return OutputColor(input.color);
}

float4 PS_Texture(VS_OUTPUT input) : SV_Target
{
	return OutputColor(texture0.Sample(sampler0, input.tex) * input.color);
}

float4 PS_SquareDot(VS_OUTPUT input) : SV_Target
{
	const float tr = input.tex.y;
	const float d = abs(fmod(input.tex.x, 3.0) - 1.0);
	const float range = 1.0 - tr;
	input.color.a *= (d < range) ? 1.0 : (d < 1.0) ? ((1.0 - d) / tr) : 0.0;
	return OutputColor(input.color);
}

float4 PS_RoundDot(VS_OUTPUT input) : SV_Target
{
	const float t = fmod(input.tex.x, 2.0);
	input.tex.x = abs(1 - t) * 2.0;
	input.color.a *= 1.0 - saturate(pow(dot(input.tex, input.tex), 8));
	return OutputColor(input.color);
}

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}

float4 PS_SDF(VS_OUTPUT input) : SV_Target
{
	const float pxRange = g_sdfParam.x;
	float2 size;
	texture0.GetDimensions(size.x, size.y);
	const float2 msdfUnit = pxRange / size;
	const float3 s = texture0.Sample(sampler0, input.tex).rgb;
	float sigDist = median(s.r, s.g, s.b) - 0.5;
	sigDist *= dot(msdfUnit, 0.5 / fwidth(input.tex));
	const float a = saturate(sigDist + 0.5);

	return OutputColor(float4(input.color.rgb, input.color.a * a));
}
