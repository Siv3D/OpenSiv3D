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

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}
		
void main()
{
	float pxRange = g_sdfParam.x;
	vec2 size = textureSize(Tex0, 0);
	vec2 msdfUnit = pxRange / size;
	vec3 s = texture(Tex0, Tex).rgb;
	float sigDist = median(s.r, s.g, s.b) - 0.5;
	sigDist *= dot(msdfUnit, 0.5 / fwidth(Tex));
	float a = clamp(sigDist + 0.5, 0.0, 1.0);

	FragColor = OutputColor(vec4(Color.rgb, Color.a * a));
}
