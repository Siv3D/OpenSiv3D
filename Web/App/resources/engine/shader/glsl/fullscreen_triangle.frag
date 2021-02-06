#version 300 es

//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

precision mediump float;
uniform sampler2D Texture0;

//
// PSInput
//
in vec2 UV;
		
//
// PSOutput
//
layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Texture0, UV);
}
