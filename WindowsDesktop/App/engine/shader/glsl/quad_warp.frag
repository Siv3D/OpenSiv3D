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
	vec4 g_internal;
};

layout(std140) uniform PSQuadWarp
{
	mat3x3 g_invHomography;
	vec4 g_uvTransform;
};

vec2 Transform(vec2 pos, mat3x3 mat)
{
	float s = (mat[0][2] * pos.x + mat[1][2] * pos.y + mat[2][2]);
	float x = (mat[0][0] * pos.x + mat[1][0] * pos.y + mat[2][0]) / s;
	float y = (mat[0][1] * pos.x + mat[1][1] * pos.y + mat[2][1]) / s;
	return vec2(x, y);
}

//
//	Functions
//
void main()
{
	vec2 uv = (Transform(UV, g_invHomography) * g_uvTransform.xy + g_uvTransform.zw);	

	vec4 texColor = texture(Texture0, uv);

	FragColor = ((texColor * Color) + g_colorAdd);
}
