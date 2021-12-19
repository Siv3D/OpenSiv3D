# version 300 es

//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

precision mediump float;

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
in vec4 Color;
in vec2 UV;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
	vec4 g_sdfOutlineColor;
	vec4 g_sdfShadowColor;
};

layout(std140) uniform PSHomography
{
	mat3x3 g_invHomography;
};

//
//	Functions
//
vec2 Transform(vec2 pos, mat3x3 mat)
{
	float s = (mat[0][2] * pos.x + mat[1][2] * pos.y + mat[2][2]);
	float x = (mat[0][0] * pos.x + mat[1][0] * pos.y + mat[2][0]) / s;
	float y = (mat[0][1] * pos.x + mat[1][1] * pos.y + mat[2][1]) / s;
	return vec2(x, y);
}

void main()
{
	vec2 uv = Transform(UV, g_invHomography);
	vec4 texColor = texture(Texture0, uv);

	FragColor = ((texColor * Color) + g_colorAdd);
}
