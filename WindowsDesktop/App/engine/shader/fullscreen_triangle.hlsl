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

cbuffer VSConstantsFullscreenTriangle : register(b0)
{
	float4 g_texScale;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

PSInput VS_Resolve(uint id: SV_VERTEXID)
{
	PSInput result;

	result.position.x = (float)(id / 2) * 4.0 - 1.0;
	result.position.y = (float)(id % 2) * 4.0 - 1.0;
	result.position.z = 0.0;
	result.position.w = 1.0;

	result.color = 1.0;

	result.uv.x = (float)(id / 2) * 2.0;
	result.uv.y = 1.0 - (float)(id % 2) * 2.0;
	result.uv *= g_texScale.xy;

	return result;
}

PSInput VS_Draw(uint id: SV_VERTEXID)
{
	PSInput result;

	result.position.x = (float)(id / 2) * 4.0 - 1.0;
	result.position.y = (float)(id % 2) * 4.0 - 1.0;
	result.position.z = 0.0;
	result.position.w = 1.0;

	result.color = 1.0;

	result.uv.x = (float)(id / 2) * 2.0;
	result.uv.y = 1.0 - (float)(id % 2) * 2.0;

	return result;
}
