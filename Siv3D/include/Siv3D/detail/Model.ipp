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
	inline bool Model::RegisterDiffuseTextures(const Model& model, const TextureDesc textureDesc)
	{
		bool result = true;

		for (const auto& textureName : model.diffuseTextureNames())
		{
			if (not TextureAsset::IsRegistered(textureName))
			{
				result &= TextureAsset::Register(textureName, textureName, textureDesc);
			}
		}

		return result;
	}
}

template <>
inline void std::swap(s3d::Model& a, s3d::Model& b) noexcept
{
	a.swap(b);
}
