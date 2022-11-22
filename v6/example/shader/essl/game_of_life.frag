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

	float n = 0.0f;

	for (uint i = 0u; i < 8u; ++i)
	{
		n += texture(Texture0, UV + offsets[i] * g_pixelSize).r;
	}

	if((c == 0.0f && n == 3.0f) || (c == 1.0f && (n == 2.0f || n == 3.0f)))
	{
		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
