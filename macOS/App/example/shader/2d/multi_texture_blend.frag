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
	vec4 texColor0 = texture(Texture0, UV);
	
	vec4 texColor1 = texture(Texture1, UV);
	
	texColor0.rgb = (texColor0.rgb * 0.5 + texColor1.rgb * 0.5);

	FragColor = (texColor0 * Color) + g_colorAdd;
}
