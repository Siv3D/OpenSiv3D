//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr PhongMaterial::PhongMaterial(const ColorF& _diffuseColor, const HasDiffuseTexture _hasDiffuseTexture)
		: diffuseColor{ _diffuseColor }
		, hasDiffuseTexture{ _hasDiffuseTexture.getBool() } {}

	inline PhongMaterial::PhongMaterial(const Material& material, const HasDiffuseTexture _hasDiffuseTexture)
		: ambientColor{ material.ambient }
		, diffuseColor{ material.diffuse }
		, specularColor{ material.specular }
		, emissionColor{ material.emission }
		, shininess{ material.shininess }
		, hasDiffuseTexture{ _hasDiffuseTexture.getBool() } {}

	inline constexpr PhongMaterialInternal::PhongMaterialInternal(const PhongMaterial& m) noexcept
		: ambientColor{ m.ambientColor.rgb() }
		, hasDiffuseTexture{ m.hasDiffuseTexture }
		, diffuseColor{ m.diffuseColor.toFloat4() }
		, specularColor{ m.specularColor.rgb() }
		, shininess{ static_cast<float>(m.shininess) }
		, emissionColor{ m.emissionColor.rgb() } {}
}
