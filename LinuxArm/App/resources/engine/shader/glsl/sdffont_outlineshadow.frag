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
void main()
{
	float d = texture(Texture0, UV).a;

	float od = (d - g_sdfParam.y);
	float outlineAlpha = clamp(od / fwidth(od) + 0.5, 0.0, 1.0);

	float td = (d - g_sdfParam.x);
	float textAlpha = clamp(td / fwidth(td) + 0.5, 0.0, 1.0);

	float baseAlpha = (outlineAlpha - textAlpha);

	vec4 textColor;
	textColor.rgb = mix(g_sdfOutlineColor.rgb, Color.rgb, textAlpha);
	textColor.a = baseAlpha * g_sdfOutlineColor.a + textAlpha * Color.a;


	vec2 size = textureSize(Texture0, 0);
	vec2 shadowOffset = (g_sdfParam.zw / size);
	float d2 = texture(Texture0, UV - shadowOffset).a;

	float sd = (d2 - g_sdfParam.y);
	float shadowAlpha = clamp(sd / fwidth(sd) + 0.5, 0.0, 1.0);
	float sBase = shadowAlpha * (1.0 - textColor.a);

	vec4 color;
	if (textColor.a == 0.0)
	{
		color.rgb = g_sdfShadowColor.rgb;
	}
	else
	{
		color.rgb = mix(textColor.rgb, g_sdfShadowColor.rgb, sBase);
	}
	color.a = (sBase * g_sdfShadowColor.a) + textColor.a;

	FragColor = (color + g_colorAdd);
}
