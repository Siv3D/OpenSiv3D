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

namespace s3d
{
	inline PhongMaterial::PhongMaterial(const ColorF& _diffuseColor, const HasDiffuseTexture _hasDiffuseTexture)
		: diffuseColor{ _diffuseColor }
		, hasDiffuseTexture{ _hasDiffuseTexture.getBool() } {}

	inline PhongMaterial::PhongMaterial(const Material& material, const HasDiffuseTexture _hasDiffuseTexture)
		: amibientColor{ material.ambient }
		, diffuseColor{ material.diffuse }
		, specularColor{ material.specular }
		, emissionColor{ material.emission }
		, shininess{ material.shininess }
		, hasDiffuseTexture{ _hasDiffuseTexture.getBool() } {}

	inline constexpr PhongMaterialInternal::PhongMaterialInternal(const PhongMaterial& m) noexcept
		: amibientColor{ m.amibientColor.rgb() }
		, hasDiffuseTexture{ m.hasDiffuseTexture }
		, diffuseColor{ m.diffuseColor.toFloat4() }
		, specularColor{ m.specularColor.rgb() }
		, shininess{ static_cast<float>(m.shininess) }
		, emissionColor{ m.emissionColor.rgb() } {}
}
