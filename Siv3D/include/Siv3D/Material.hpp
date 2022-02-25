//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "ColorHSV.hpp"
# include "String.hpp"

namespace s3d
{
	struct Material
	{
		String name;

		ColorF ambient = ColorF{ 1.0 };

		ColorF diffuse = ColorF{ 1.0 };

		ColorF specular = ColorF{ 0.0 };

		ColorF transmittance = ColorF{ 0.0 };

		ColorF emission = ColorF{ 0.0 };

		float shininess = 128.0f;

		float ior = 0.0f;

		float dissolve = 0.0f;

		int32 illum = 0;

		String ambientTextureName;

		String diffuseTextureName;

		String specularTextureName;

		String normalTextureName;
	};
}
