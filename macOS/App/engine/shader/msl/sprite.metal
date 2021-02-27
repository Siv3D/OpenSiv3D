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
	//	VS Input
	//
	struct Vertex2D
	{
		float2 pos [[attribute(0)]];
		float2 uv [[attribute(1)]];
		float4 color [[attribute(2)]];
	};

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
vertex
s3d::PSInput VS_Sprite(s3d::Vertex2D in [[stage_in]],
				  constant VSConstants2D& cb [[buffer(0)]])
{
	s3d::PSInput result;
	result.clipSpacePosition	= s3d::Transform2D(in.pos, cb.transform);
	result.uv					= in.uv;
	result.color				= (in.color * cb.colorMul);
	return result;
}

fragment
float4 PS_Shape(s3d::PSInput in [[stage_in]],
				constant PSConstants2D& cb [[buffer(0)]])
{
    return (in.color + cb.colorAdd);
}

fragment
float4 PS_SquareDot(s3d::PSInput in [[stage_in]],
				constant PSConstants2D& cb [[buffer(0)]])
{
    return (in.color + cb.colorAdd);
}

fragment
float4 PS_RoundDot(s3d::PSInput in [[stage_in]],
				constant PSConstants2D& cb [[buffer(0)]])
{
    return (in.color + cb.colorAdd);
}

vertex
s3d::PSInput VS_FullscreenTriangle(uint id [[vertex_id]])
{
	s3d::PSInput result;
	result.clipSpacePosition.x = (float)(id / 2) * 4.0 - 1.0;
	result.clipSpacePosition.y = (float)(id % 2) * 4.0 - 1.0;
	result.clipSpacePosition.z = 0.0;
	result.clipSpacePosition.w = 1.0;
	result.color = 1.0;
	result.uv.x = (float)(id / 2) * 2.0;
	result.uv.y = 1.0 - (float)(id % 2) * 2.0;
	return result;
}

fragment
float4 PS_FullscreenTriangle(s3d::PSInput in [[stage_in]],
				texture2d<float> colorTexture [[texture(0)]],
				sampler smp [[sampler(0)]])
{
	//constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
	return float4(colorTexture.sample(smp, in.uv).rgb, 1);
}
