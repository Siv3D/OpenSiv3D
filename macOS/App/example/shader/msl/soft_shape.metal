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

# include <metal_stdlib>
using namespace metal;

namespace s3d
{
	//
	//	VS Input (nothing)
	//

	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 clipSpacePosition [[position]];
		float2 uv;
		float4 color;
	};

	//
	//	Siv3D Functions
	//
	inline float4 Transform2D(float2 pos, constant float4(&t)[2])
	{
		return float4(t[0].zw + (pos.x * t[0].xy) + (pos.y * t[1].xy), t[1].zw);
	}
}

//
//	Constant Buffer
//
struct VSConstants2D
{
	float4 transform[2];
	float4 colorMul;
};

struct PSConstants2D
{
	float4 colorAdd;
	float4 sdfParam;
	float4 internal;
};

//
//	Functions
//
float Radians(float degree)
{
	return degree / 360.0f * M_PI_F * 2.0f;
}

float2 Circular(float r, float theta)
{
	return float2(sin(theta), -cos(theta)) * r;
}

vertex
s3d::PSInput VS_SoftShape(uint id [[vertex_id]],
				  constant VSConstants2D& cb [[buffer(1)]])
{
	s3d::PSInput result;
	result.color = float4(0.2, 0.7, 0.4, 1);
	
	float2 pos;
	float g_t = 0.0f;

	if (id % 3 == 0)
	{
		pos = float2(640, 360);
	}
	else
	{
		const float angle = Radians((id / 3) + ((id % 3) - 1));
		const float r = 200
			+ cos((angle * 2) + sin(g_t * 1.5)) * 40
			+ sin((angle * 2) + sin(g_t * 2.0)) * 30
			+ cos((angle * 3) + sin(g_t * 3.5)) * 20
			+ sin((angle * 3) + sin(g_t * 4.0)) * 10;
		pos = float2(640, 360) + Circular(r, angle);
		result.color.a = (1.0 - r / 360.0);
	}
	
	result.clipSpacePosition	= s3d::Transform2D(pos, cb.transform);
	result.uv					= float2(0, 0);
	return result;
}
