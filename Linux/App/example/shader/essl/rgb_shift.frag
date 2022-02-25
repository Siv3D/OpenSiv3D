# version 300 es

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
	vec4 g_internal;
};

//
//	Functions
//
void main()
{
	vec2 ra = texture(Texture0, UV + vec2(-0.02, 0.0)).ra;
	vec2 ga = texture(Texture0, UV).ga;
	vec2 ba = texture(Texture0, UV + vec2(+0.02, 0.0)).ba;

	float a = (ra.y + ga.y + ba.y) / 3.0f;
	vec4 texColor = vec4(ra.x, ga.x, ba.x, a);	

	FragColor = (texColor * Color) + g_colorAdd;
}
