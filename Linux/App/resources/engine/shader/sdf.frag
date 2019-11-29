#version 410

uniform sampler2D Texture0;

layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
	vec4 g_internal;	
};

//
// PSInput
//
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 UV;

//
// PSOutput
//
layout(location = 0) out vec4 FragColor;

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}
		
void main()
{
	float pxRange = g_sdfParam.x;
	vec2 size = textureSize(Texture0, 0);
	vec2 msdfUnit = pxRange / size;
	vec3 s = texture(Texture0, UV).rgb;
	float sigDist = median(s.r, s.g, s.b) - 0.5 + g_sdfParam.y;
	sigDist *= dot(msdfUnit, 0.5 / fwidth(UV));
	
	float a = clamp(sigDist + 0.5, 0.0, 1.0);
	vec4 color = vec4(Color.rgb, Color.a * a);

	FragColor = color + g_colorAdd;
}
