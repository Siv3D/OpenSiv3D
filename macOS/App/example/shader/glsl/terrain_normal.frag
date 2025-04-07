//	Copyright (c) 2008-2025 Ryo Suzuki.
//	Copyright (c) 2016-2025 OpenSiv3D Project.
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
layout(location = 0) out vec2 FragColor;

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
	vec2 size = textureSize(Texture0, 0);
	vec2 offset = vec2(1.0f, 1.0f) / size;

	float n = texture(Texture0, UV + vec2(0, -offset.y)).r;
	float s = texture(Texture0, UV + vec2(0,  offset.y)).r;
	float w = texture(Texture0, UV + vec2(-offset.x, 0)).r;
	float e = texture(Texture0, UV + vec2( offset.x, 0)).r;

	vec3 normal = normalize(vec3(w - e, 2.0f, s - n));

	FragColor = normal.xz;
}
