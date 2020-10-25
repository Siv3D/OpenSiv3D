
# include <metal_stdlib>
using namespace metal;

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

struct Vertex2D
{
	float2 pos [[attribute(0)]];
	float2 uv [[attribute(1)]];
	float4 color [[attribute(2)]];
};

struct PSInput
{
	float4 clipSpacePosition [[position]];
	float2 uv;
	float4 color;
};

float4 StandardTransform(float2 pos,
						 constant float4(&transform)[2])
{
	float4 result;
	result.xy = transform[0].zw + pos.x * transform[0].xy + pos.y * transform[1].xy;
	result.zw = transform[1].zw;
	return result;
}

vertex
PSInput VS_Sprite(Vertex2D in [[stage_in]],
				  constant VSConstants2D& cb [[buffer(1)]])
{
	PSInput out;
	out.clipSpacePosition = StandardTransform(in.pos, cb.transform);
	out.uv = in.uv;
	out.color = (in.color * cb.colorMul);
	return out;
}

fragment
float4 PS_Shape(PSInput in [[stage_in]],
				constant PSConstants2D& cb [[buffer(1)]])
{
    return (in.color + cb.colorAdd);
}

vertex
PSInput VS_FullscreenTriangle(uint id [[vertex_id]])
{
	PSInput result;
	
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
float4 PS_FullscreenTriangle(PSInput in [[stage_in]],
				texture2d<float> colorTexture [[texture(0)]],
				sampler smp [[sampler(0)]])
{
	//constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
	return float4(colorTexture.sample(smp, in.uv).rgb, 1);
}

