#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Tex0;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = texture(Tex0, Tex) * Color;
}
