#version 410
		
uniform sampler2D Texture0;

// PS_0
layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
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
//	Float3 _unused = 0.0f;
//};

//
// PSInput
//
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 UV;
		
//
// PSOutput
//
layout(location = 0) out vec4 FragColor;
		
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
