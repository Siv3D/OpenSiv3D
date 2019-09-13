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
	vec2 g_pixelSize;
	vec2 g_direction;
};

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}

//
// http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
//
void main()
{
	vec2 offset1 = 1.41176470588235 * g_direction;
	vec2 offset2 = 3.29411764705882 * g_direction;
	vec2 offset3 = 5.17647058823529 * g_direction;

	vec4 color = texture(Texture0, Tex) * 0.19648255015114;
	color += texture(Texture0, Tex + (offset1 * g_pixelSize)) * 0.296906964672834;
	color += texture(Texture0, Tex - (offset1 * g_pixelSize)) * 0.296906964672834;
	color += texture(Texture0, Tex + (offset2 * g_pixelSize)) * 0.094470397850447;
	color += texture(Texture0, Tex - (offset2 * g_pixelSize)) * 0.094470397850447;
	color += texture(Texture0, Tex + (offset3 * g_pixelSize)) * 0.010381362401148;
	color += texture(Texture0, Tex - (offset3 * g_pixelSize)) * 0.010381362401148;

	FragColor = color;
}
