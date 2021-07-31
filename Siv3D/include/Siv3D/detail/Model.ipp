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

namespace s3d
{
	inline void Model::RegisterDiffuseTextures(const Model& model, const TextureDesc textureDesc)
	{
		for (const auto& material : model.materials())
		{
			if (const auto& textureName = material.diffuseTextureName;
				(textureName && (not TextureAsset::IsRegistered(textureName))))
			{
				TextureAsset::Register(textureName, textureName, textureDesc);
			}
		}
	}
}

template <>
inline void std::swap(s3d::Model& a, s3d::Model& b) noexcept
{
	a.swap(b);
}
