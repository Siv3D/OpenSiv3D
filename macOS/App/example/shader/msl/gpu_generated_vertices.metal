
# include <metal_stdlib>
using namespace metal;

struct VSConstants2D
{
	float4 transform[2];
	float4 colorMul;
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

inline float4 StandardTransform(float2 pos,
						 constant float4(&transform)[2])
{
	float4 result;
	result.xy = transform[0].zw + pos.x * transform[0].xy + pos.y * transform[1].xy;
	result.zw = transform[1].zw;
	return result;
}

inline float ToRadians(float degree)
{
	return degree / (360.0f * 3.141592653589793f);
}

vertex
PSInput VS_GPU_Generate(uint id [[vertex_id]],
				  constant VSConstants2D& cb [[buffer(1)]])
{
	PSInput out;
	
	float2 pos;
	
	if (id % 3 == 0)
	{
		pos = float2(640, 360);
	}
	else
	{
		const float angle = ToRadians((id / 3) + ((id % 3) - 1));
		const float r = 200
			+ sin(angle * 4) * 10
			+ cos(angle * 6) * 20
			+ cos(angle * 12) * 40;
		pos = float2(640, 360) + float2(sin(angle), -cos(angle)) * r;
	}
	
	out.clipSpacePosition = StandardTransform(pos, cb.transform);
	out.uv = float2(0, 0);
	out.color = float4(1, 1, 1, 1);
	return out;
}
/*
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
*/
