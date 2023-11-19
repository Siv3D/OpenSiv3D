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
	vec2 offset1 = (1.41176470588235 * g_direction);
	vec2 offset2 = (3.29411764705882 * g_direction);
	vec2 offset3 = (5.17647058823529 * g_direction);

	vec4 color = (texture(Texture0, UV) * 0.196482550151140);
	color += (texture(Texture0, UV + (offset1 * g_pixelSize)) * 0.296906964672834);
	color += (texture(Texture0, UV - (offset1 * g_pixelSize)) * 0.296906964672834);
	color += (texture(Texture0, UV + (offset2 * g_pixelSize)) * 0.0944703978504473);
	color += (texture(Texture0, UV - (offset2 * g_pixelSize)) * 0.0944703978504473);
	color += (texture(Texture0, UV + (offset3 * g_pixelSize)) * 0.0103813624011481);
	color += (texture(Texture0, UV - (offset3 * g_pixelSize)) * 0.0103813624011481);

	FragColor = color;
}
