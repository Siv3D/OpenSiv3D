#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Tex0;
		
layout(location = 0) out vec4 FragColor;

layout(std140) uniform pscbSprite
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
	vec2 ra = texture(Tex0, Tex + vec2(-0.02, 0.0)).ra;
	vec2 ga = texture(Tex0, Tex + vec2(0.0, 0.0)).ga;
	vec2 ba = texture(Tex0, Tex + vec2(+0.02, 0.0)).ba;
	vec4 texColor = vec4(ra.x, ga.x, ba.x, (ra.y + ga.y + ba.y) / 3);	

	FragColor = OutputColor(texColor * Color);
}
