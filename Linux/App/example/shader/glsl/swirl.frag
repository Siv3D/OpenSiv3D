//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
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

// PS_1
layout(std140) uniform Swirl
{
	float g_angle;
};
// [C++]
//struct PoissonDisk
//{
//	float angle;
//};

//
//	Functions
//
void main()
{
	vec2 uv = UV - vec2(0.5, 0.5);

	float distanceFromCenter = length(uv);

	float angle = distanceFromCenter * g_angle;

	float c = cos(angle), s = sin(angle);

	uv = mat2x2(c, -s, s, c) * uv + vec2(0.5, 0.5);

	vec4 texColor = texture(Texture0, uv);

	FragColor = (texColor * Color) + g_colorAdd;
}
