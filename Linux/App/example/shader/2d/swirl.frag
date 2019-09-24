#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Texture0;
		
layout(location = 0) out vec4 FragColor;

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

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}
		
void main()
{
	vec2 uv = Tex - vec2(0.5, 0.5);

	float distanceFromCenter = length(uv);

	float angle = distanceFromCenter * g_angle;

	float c = cos(angle), s = sin(angle);

	uv = mat2x2(c, -s, s, c) * uv + vec2(0.5, 0.5);

	FragColor = OutputColor(texture(Texture0, uv) * Color);
}
