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
layout(std140) uniform PoissonDisk
{
	vec2  g_pixelSize;
	float g_diskRadius;
};
// [C++]
//struct PoissonDisk
//{
//	Float2 pixelSize;
//	float diskRadius;
//};

const vec2 poisson[12] = vec2[12](
       vec2(-0.326212, -0.405805),
       vec2(-0.840144, -0.07358),
       vec2(-0.695914, 0.457137),
       vec2(-0.203345, 0.620716),
       vec2(0.96234, -0.194983),
       vec2(0.473434, -0.480026),
       vec2(0.519456, 0.767022),
       vec2(0.185461, -0.893124),
       vec2(0.507431, 0.064425),
       vec2(0.89642, 0.412458),
       vec2(-0.32194, -0.932615),
       vec2(-0.791559, -0.597705)
);

//
//	Functions
//
void main()
{
	vec2 offsetScale = g_pixelSize * g_diskRadius;

	vec4 accum = texture(Texture0, UV);

	for (uint tap = 0u; tap < 12u; ++tap)
	{
		vec2 uv = UV + (poisson[tap] * offsetScale);

		accum += texture(Texture0, uv);
	}

	accum /= 13.0f;

	FragColor = (accum * Color) + g_colorAdd;
}
