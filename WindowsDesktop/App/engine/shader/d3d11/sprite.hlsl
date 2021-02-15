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
	//	VS Input
	//
	struct VSInput
	{
		float2 position	: POSITION;
		float2 uv		: TEXCOORD0;
		float4 color	: COLOR0;
	};

	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};

	//
	//	Siv3D Functions
	//
	float4 Transform2D(float2 pos, float2x4 t)
	{
		return float4((t._13_14 + (pos.x * t._11_12) + (pos.y * t._21_22)), t._23_24);
	}

	float median(float r, float g, float b)
	{
		return max(min(r, g), min(max(r, g), b));
	}
}

//
//	Constant Buffer
//
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

//
//	Functions
//
s3d::PSInput VS(s3d::VSInput input)
{
	s3d::PSInput result;
	result.position	= s3d::Transform2D(input.position, g_transform);
	result.color	= input.color * g_colorMul;
	result.uv		= input.uv;
	return result;
}

float4 PS_Shape(s3d::PSInput input) : SV_TARGET
{
	return (input.color + g_colorAdd);
}

float4 PS_Texture(s3d::PSInput input) : SV_TARGET
{
	const float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

	return ((texColor * input.color) + g_colorAdd);
}

float4 PS_BitmapFont(s3d::PSInput input) : SV_TARGET
{
	const float textAlpha = g_texture0.Sample(g_sampler0, input.uv).a;

	input.color.a *= textAlpha;

	return (input.color + g_colorAdd);
}

float4 PS_SDFFont(s3d::PSInput input) : SV_TARGET
{
	const float d = g_texture0.Sample(g_sampler0, input.uv).a;

	const float td = (d - 0.5);
	const float textAlpha = saturate(td / fwidth(td) + 0.5);

	input.color.a *= textAlpha;

	return (input.color + g_colorAdd);
}

float4 PS_MSDFFont(s3d::PSInput input) : SV_TARGET
{
	float2 size; g_texture0.GetDimensions(size.x, size.y);
	const float pxRange = 4.0;
	const float2 msdfUnit = (pxRange / size);

	const float3 s = g_texture0.Sample(g_sampler0, input.uv).rgb;
	const float d = s3d::median(s.r, s.g, s.b);

	const float td = (d - 0.5);
	const float textAlpha = saturate(td * dot(msdfUnit, 0.5 / fwidth(input.uv)) + 0.5);

	input.color.a *= textAlpha;

	return (input.color + g_colorAdd);
}

float4 PS_MSDFPrint(s3d::PSInput input) : SV_TARGET
{
	float2 size; g_texture0.GetDimensions(size.x, size.y);
	const float pxRange = 4.0;
	const float2 msdfUnit = (pxRange / size);

	const float3 s = g_texture0.Sample(g_sampler0, input.uv).rgb;
	const float d = s3d::median(s.r, s.g, s.b);

	const float td = (d - 0.5);
	const float textAlpha = sqrt(saturate(td * dot(msdfUnit, 0.5 / fwidth(input.uv)) + 0.5));

	const float2 shadowOffset = float2(0.875, 0.875) / size;
	const float3 s2 = g_texture0.Sample(g_sampler0, input.uv - shadowOffset).rgb;
	const float d2 = s3d::median(s2.r, s2.g, s2.b);
	const float sd = (d2 - 0.5);
	const float shadowAlpha = sqrt(saturate(sd * dot(msdfUnit, 0.5 / fwidth(input.uv)) + 0.5));

	return float4(textAlpha, textAlpha, textAlpha, max(textAlpha, shadowAlpha));
}







/*
float4 PS_SquareDot(s3d::PSInput input) : SV_TARGET
{
	float tr = input.uv.y;
	
	float d = abs(fmod(input.uv.x, 3.0) - 1.0);

	float range = 1.0 - tr;
	
	input.color.a *= (d < range) ? 1.0 : (d < 1.0) ? ((1.0 - d) / tr) : 0.0;
	
	return input.color + g_colorAdd;
}

float4 PS_RoundDot(s3d::PSInput input) : SV_TARGET
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

float4 PS_SDF(s3d::PSInput input) : SV_TARGET
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
*/