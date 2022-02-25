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

//
//	Functions
//
vec3 ApplySRGBCurve_Fast(vec3 color)
{
	return pow(color, vec3(1.0f / 2.2f));
}

void main()
{
	vec3 texColor = texture(Texture0, UV).rgb;

	float brightness = dot(texColor, vec3(0.2126f, 0.7152f, 0.0722f));

	if (0.25f < brightness)
	{
		FragColor = vec4(ApplySRGBCurve_Fast(abs(texColor)) * 0.25f, 1.0f);
	}
	else
	{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
