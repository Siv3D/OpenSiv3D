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

Texture2DMS<float4, 4> g_texture0 : register(t0);

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
	float4 texColor0 = g_texture0.Load(input.uv, 0);
	float4 texColor1 = g_texture0.Load(input.uv, 1);
	float4 texColor2 = g_texture0.Load(input.uv, 2);
	float4 texColor3 = g_texture0.Load(input.uv, 3);
	float4 texColor  = texColor0 + texColor1 + texColor2 + texColor3;

	return float4(texColor.rgb / 4, 1);
}
