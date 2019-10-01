#version 410		

uniform sampler2D Texture0;
uniform sampler2D Texture1;

// PS_0
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
		
void main()
{
	vec4 texColor = texture(Texture0, UV);
	
	float mask = texture(Texture1, UV).r;

	texColor.a *= mask;

	FragColor = (texColor * Color) + g_colorAdd;
}
