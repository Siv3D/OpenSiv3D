//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
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
	vec2 g_pixelSize;
	vec2 g_direction;
};

//
//	Functions
//
void main()
{
	vec2 offset1 = (1.33333333333333 * g_direction);

	vec4 color = (texture(Texture0, UV) * 0.294117647058824);
	color += (texture(Texture0, UV + (offset1 * g_pixelSize)) * 0.352941176470588);
	color += (texture(Texture0, UV - (offset1 * g_pixelSize)) * 0.352941176470588);

	FragColor = color;
}
