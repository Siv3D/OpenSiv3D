#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Texture0;
uniform sampler2D Texture1;
		
layout(location = 0) out vec4 FragColor;

// PS_0
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
	vec4 texColor0 = texture(Texture0, Tex);
	vec4 texColor1 = texture(Texture1, Tex);
	texColor0.rgb = (texColor0.rgb * 0.5 + texColor1.rgb * 0.5);

	FragColor = OutputColor(texColor0 * Color);
}
