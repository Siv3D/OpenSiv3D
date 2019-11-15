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

Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);

cbuffer VSConstants2D : register(b0)
{
	row_major float2x4 g_transform;
	float4 g_colorMul;
}

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_internal;
}

struct VSInput
{
	float2 position	: POSITION;
	float2 uv		: TEXCOORD0;
	float4 color	: COLOR0;
};

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float4 StandardTransform(float2 pos)
{
	float4 result;
	result.xy	= g_transform._13_14 + pos.x * g_transform._11_12 + pos.y * g_transform._21_22;
	result.z	= g_transform._23;
	result.w	= g_transform._24;
	return result;
}

PSInput VS(VSInput input)
{
	PSInput result;
	result.position	= StandardTransform(input.position);
	result.color	= input.color * g_colorMul;
	result.uv		= input.uv;
	return result;
}

float4 PS_Shape(PSInput input) : SV_TARGET
{
	return input.color + g_colorAdd;
}

float4 PS_Texture(PSInput input) : SV_TARGET
{
	float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

	return (texColor * input.color) + g_colorAdd;
}

float4 PS_SquareDot(PSInput input) : SV_TARGET
{
	float tr = input.uv.y;
	
	float d = abs(fmod(input.uv.x, 3.0) - 1.0);

	float range = 1.0 - tr;
	
	input.color.a *= (d < range) ? 1.0 : (d < 1.0) ? ((1.0 - d) / tr) : 0.0;
	
	return input.color + g_colorAdd;
}

float4 PS_RoundDot(PSInput input) : SV_TARGET
{
	float t = fmod(input.uv.x, 2.0);
	
	input.uv.x = abs(1 - t) * 2.0;
	
	input.color.a *= 1.0 - saturate(pow(dot(input.uv, input.uv), 8));
	
	return input.color + g_colorAdd;
}

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}

float4 PS_SDF(PSInput input) : SV_TARGET
{
	float pxRange = g_sdfParam.x;
	
	float2 size;
	g_texture0.GetDimensions(size.x, size.y);
	
	float2 msdfUnit = pxRange / size;
	
	float3 s = g_texture0.Sample(g_sampler0, input.uv).rgb;
	
	float sigDist = median(s.r, s.g, s.b) - 0.5 + g_sdfParam.y;
	
	sigDist *= dot(msdfUnit, 0.5 / fwidth(input.uv));
	
	float a = saturate(sigDist + 0.5);

	input.color.a *= a;

	return input.color + g_colorAdd;
}
