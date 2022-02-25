#version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
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

//
//	Functions
//
float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}

void main()
{
	vec2 size = vec2(textureSize(Texture0, 0));
	const float pxRange = 4.0;
	vec2 msdfUnit = (pxRange / size);

	vec3 s = texture(Texture0, UV).rgb;
	float d = median(s.r, s.g, s.b);

	float od = (d - g_sdfParam.y);
	float outlineAlpha = clamp(od * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0);

	float td = (d - g_sdfParam.x);
	float textAlpha = clamp(td * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0);

	float baseAlpha = (outlineAlpha - textAlpha);

	vec4 color;
	color.rgb = mix(g_sdfOutlineColor.rgb, Color.rgb, textAlpha);
	color.a = baseAlpha * g_sdfOutlineColor.a + textAlpha * Color.a;

	FragColor = (color + g_colorAdd);
}
