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
	float tr = Tex.y;
	float d = abs(mod(Tex.x, 3.0) - 1.0);
	float range = 1.0 - tr;
	vec4 color = Color;
	color.a *= (d < range) ? 1.0 : (d < 1.0) ? ((1.0 - d) / tr) : 0.0;
	FragColor = OutputColor(color);	
}
