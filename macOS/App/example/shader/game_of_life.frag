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
};

// PS_1
layout(std140) uniform GameOfLife
{
	vec2  g_pixelSize;
	float g_discRadius;
};
// [C++]
//struct GameOfLife
//{
//	Float2 pixelSize;
//	Float2 _unused = {};
//};

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}

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
	float c = texture(Texture0, Tex).r;
	float n = 0;

	for (int i = 0; i < 8; ++i)
	{
		n += texture(Texture0, Tex + offsets[i] * g_pixelSize).r;
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
