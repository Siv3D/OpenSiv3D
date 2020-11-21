//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

cbuffer VSConstants2D : register(b0)
{
	row_major float2x4 g_transform;
	float4 g_colorMul;
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

PSInput VS(uint id: SV_VERTEXID)
{
	PSInput result;

	float2 pos;

	if (id % 3 == 0)
	{
		pos = float2(640, 360);
	}
	else
	{
		const float angle = radians((id / 3) + ((id % 3) - 1));
		const float r = 200
			+ sin(angle * 4) * 10
			+ cos(angle * 6) * 20
			+ cos(angle * 12) * 40;
		pos = float2(640, 360) + float2(sin(angle), -cos(angle)) * r;
	}

	result.position	= StandardTransform(pos);
	result.color	= float4(0.4, 0.6, 0.8, 1);
	result.uv		= float2(0, 0);
	return result;
}
