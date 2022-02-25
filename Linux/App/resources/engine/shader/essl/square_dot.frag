#version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

precision mediump float;

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

//
//	Functions
//
void main()
{
	float tr = UV.y;
	float d = abs(mod(UV.x, 3.0) - 1.0);
	float range = 1.0 - tr;
	vec4 color = Color;
	color.a *= (d < range) ? 1.0 : (d < 1.0) ? ((1.0 - d) / tr) : 0.0;

	FragColor = (color + g_colorAdd);
}
