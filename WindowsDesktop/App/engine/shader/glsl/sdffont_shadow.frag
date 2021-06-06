//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

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
};

//
//	Functions
//
void main()
{
	float d = texture(Texture0, UV).a;

	float td = (d - 0.5);
	float textAlpha = clamp(td / fwidth(td) + 0.5, 0.0, 1.0);
	vec4 textColor = vec4(Color.rgb, Color.a * textAlpha);

	vec2 size = textureSize(Texture0, 0);
	vec2 shadowOffset = (g_sdfParam.zw / size);
	float d2 = texture(Texture0, UV - shadowOffset).a;

	float sd = (d2 - 0.5);
	float shadowAlpha = clamp(sd / fwidth(sd) + 0.5, 0.0, 1.0);
	vec4 shadowColor = vec4(g_sdfShadowColor.rgb, g_sdfShadowColor.a * shadowAlpha);

	vec4 color = textColor;
	if (0.0 < shadowAlpha)
	{
		color.rgb = mix(shadowColor.rgb, textColor.rgb, textAlpha);
		color.a = max(shadowColor.a, textColor.a);
	}

	FragColor = (color + g_colorAdd);
}
