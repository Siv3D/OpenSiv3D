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
# include "PredefinedYesNo.hpp"
# include "Material.hpp"

namespace s3d
{
	struct PhongMaterial
	{
		ColorF amibientColor = ColorF{ 1.0 };

		ColorF diffuseColor = ColorF{ 1.0 };

		ColorF specularColor = ColorF{ 0.0 };

		ColorF emissionColor = ColorF{ 0.0 };

		double shininess = 128.0;

		bool hasDiffuseTexture = false;

		SIV3D_NODISCARD_CXX20
		PhongMaterial() = default;

		SIV3D_NODISCARD_CXX20
		PhongMaterial(const ColorF& _diffuseColor, HasDiffuseTexture _hasDiffuseTexture = HasDiffuseTexture::No);

		SIV3D_NODISCARD_CXX20
		PhongMaterial(const Material& material, HasDiffuseTexture _hasDiffuseTexture = HasDiffuseTexture::No);
	};

	struct PhongMaterialInternal
	{
		Float3 amibientColor = Float3{ 1.0f, 1.0f, 1.0f };
		
		uint32 hasDiffuseTexture = false;
		
		Float4 diffuseColor = Float4{ 1.0f, 1.0f, 1.0f, 1.0f };
		
		Float3 specularColor = Float3{ 0.0f, 0.0f, 0.0f };
		
		float  shininess = 128.0f;
		
		Float3 emissionColor = Float3{ 0.0f, 0.0f, 0.0f };
		
		float  _unused = 0.0f;

		SIV3D_NODISCARD_CXX20
		PhongMaterialInternal() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr PhongMaterialInternal(const PhongMaterial& m) noexcept;
	};
}

# include "detail/PhongMaterial.ipp"
