#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
layout(location = 0) out vec4 FragColor;

layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
	vec4 g_internal;	
};

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}
		
void main()
{
	float t = mod(Tex.x, 2.0);
	vec2 tex = Tex;
	tex.x = abs(1 - t) * 2.0;
	vec4 color = Color;
	color.a *= 1.0 - clamp(pow(dot(tex, tex), 8), 0.0, 1.0);
	FragColor = OutputColor(color);	
}
