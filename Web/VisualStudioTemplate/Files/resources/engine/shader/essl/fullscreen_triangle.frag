#version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

precision mediump float;

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
in vec2 UV;
		
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
