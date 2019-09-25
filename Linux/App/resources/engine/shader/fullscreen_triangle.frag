#version 410
		
layout(location = 0) in vec2 UV;
		
uniform sampler2D Texture0;

layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Texture0, UV);
}
