//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 UV;

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
	vec4 g_internal;
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
	vec2 size = textureSize(Texture0, 0);
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
