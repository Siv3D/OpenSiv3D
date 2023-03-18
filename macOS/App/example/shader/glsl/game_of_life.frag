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

// PS_1
layout(std140) uniform GameOfLife
{
	vec2  g_pixelSize;
};
// [C++]
//struct GameOfLife
//{
//	Float2 pixelSize;
//};

const vec2 offsets[8] = vec2[8](
       vec2(-1, -1),
       vec2(0, -1),
       vec2(1, -1),
       vec2(-1, 0),
       vec2(1, 0),
       vec2(-1, 1),
       vec2(0, 1),
       vec2(1, 1)
);
		
void main()
{
	float c = texture(Texture0, UV).r;

	float n = 0;

	for (uint i = 0; i < 8; ++i)
	{
		n += texture(Texture0, UV + offsets[i] * g_pixelSize).r;
	}

	if((c == 0 && n == 3) || (c == 1 && (n == 2 || n == 3)))
	{
		FragColor = vec4(1, 1, 1, 1);
	}
	else
	{
		FragColor = vec4(0, 0, 0, 1);
	}
}
