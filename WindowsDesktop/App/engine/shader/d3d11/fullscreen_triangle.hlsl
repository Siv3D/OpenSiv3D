//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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
	//	VS Input (nothing)
	//

	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};
}

//
//	Functions
//
s3d::PSInput VS(uint id: SV_VERTEXID)
{
	s3d::PSInput result;

	result.position.x = (float)(id / 2) * 4.0 - 1.0;
	result.position.y = (float)(id % 2) * 4.0 - 1.0;
	result.position.z = 0.0;
	result.position.w = 1.0;

	result.color = 1.0;

	result.uv.x = (float)(id / 2) * 2.0;
	result.uv.y = 1.0 - (float)(id % 2) * 2.0;

	return result;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

	return float4(texColor.rgb, 1);
}
