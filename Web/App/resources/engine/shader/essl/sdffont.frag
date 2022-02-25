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
	vec4 g_internal;	
};

//
//	Functions
//
void main()
{
	float d = texture(Texture0, UV).a;

	float td = (d - 0.5);
	float textAlpha = clamp(td / fwidth(td) + 0.5, 0.0, 1.0);

	vec4 color = vec4(Color.rgb, Color.a * textAlpha);

	FragColor = (color + g_colorAdd);
}
