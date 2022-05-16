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
	vec2 size = vec2(textureSize(Texture0, 0));
	vec2 offset = vec2(1.0f, 1.0f) / size;

	float n = texture(Texture0, UV + vec2(0.0f, -offset.y)).r;
	float s = texture(Texture0, UV + vec2(0.0f,  offset.y)).r;
	float w = texture(Texture0, UV + vec2(-offset.x, 0.0f)).r;
	float e = texture(Texture0, UV + vec2( offset.x, 0.0f)).r;

	vec3 normal = normalize(vec3(w - e, 2.0f, s - n));

	FragColor = normal.xz;
}
