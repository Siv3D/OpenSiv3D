#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Texture0;
uniform sampler2D Texture1;
		
layout(location = 0) out vec4 FragColor;

layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
};

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}
		
void main()
{
	vec4 texColor = texture(Texture0, Tex);
	texColor.a *= texture(Texture1, Tex).a;
	FragColor = OutputColor(texColor * Color);
}
