#version 410
		
layout(location = 0) in vec2 UV;
		
uniform sampler2D Tex0;

layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Tex0, UV);
}
