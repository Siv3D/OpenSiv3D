//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
layout(location = 0) in vec2 UV;
		
//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Functions
//
void main()
{
	FragColor = texture(Texture0, UV);
}
