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

# pragma once
# include "Common.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	struct PhongMaterial
	{
		ColorF amibientColor = ColorF{ 1.0 };

		ColorF diffuseColor = ColorF{ 1.0 };

		ColorF specularColor = ColorF{ 0.0 };

		ColorF emissionColor = ColorF{ 0.0 };

		double shinness = 128.0;

		bool hasTexture = false;
	};

	struct PhongMaterialInternal
	{
		Float3 amibientColor = Float3{ 1.0f, 1.0f, 1.0f };
		uint32 hasTexture = false;
		Float4 diffuseColor = Float4{ 1.0f, 1.0f, 1.0f, 1.0f };
		Float3 specularColor = Float3{ 0.0f, 0.0f, 0.0f };
		float  shinness = 128.0f;
		Float3 emissionColor = Float3{ 0.0f, 0.0f, 0.0f };
		float  _unused = 0.0f;

		PhongMaterialInternal() = default;

		explicit PhongMaterialInternal(const PhongMaterial& m)
			: amibientColor{ m.amibientColor.rgb() }
			, hasTexture{ m.hasTexture }
			, diffuseColor{ m.diffuseColor.toFloat4() }
			, specularColor{ m.specularColor.rgb() }
			, shinness{ static_cast<float>(m.shinness) }
			, emissionColor{ m.emissionColor.rgb() } {}
	};
}
