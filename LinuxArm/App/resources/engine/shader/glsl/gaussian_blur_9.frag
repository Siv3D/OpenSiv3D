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
	vec2 g_pixelSize;
	vec2 g_direction;
};

//
//	Functions
//
void main()
{
	//
	// http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
	//
	vec2 offset1 = 1.38461538461538 * g_direction;
	vec2 offset2 = 3.23076923076923 * g_direction;

	vec4 color = texture(Texture0, UV) * 0.227027027027027;
	color += texture(Texture0, UV + (offset1 * g_pixelSize)) * 0.316216216216216;
	color += texture(Texture0, UV - (offset1 * g_pixelSize)) * 0.316216216216216;
	color += texture(Texture0, UV + (offset2 * g_pixelSize)) * 0.070270270270270;
	color += texture(Texture0, UV - (offset2 * g_pixelSize)) * 0.070270270270270;

	FragColor = color;
}
