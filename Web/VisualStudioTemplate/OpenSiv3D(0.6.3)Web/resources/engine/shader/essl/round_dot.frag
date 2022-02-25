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
	float t = mod(UV.x, 2.0);
	vec2 tex = UV;
	tex.x = abs(1.0 - t) * 2.0;
	vec4 color = Color;

	float dist = dot(tex, tex) * 0.5;
	float delta = fwidth(dist);
	float alpha = smoothstep(0.5 - delta, 0.5, dist);
	color.a *= 1.0 - alpha;

	FragColor = (color + g_colorAdd);
}
