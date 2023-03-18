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

# include <Siv3D/ModelObject.hpp>
# include <Siv3D/TextureAsset.hpp>
# include <Siv3D/PhongMaterial.hpp>

namespace s3d
{
	void ModelObject::draw(const Array<Material>& materials) const
	{
		for (const auto& part : parts)
		{
			assert((not part.materialID) || (part.materialID < materials.size()));

			const Material material = (part.materialID ? materials[*part.materialID] : Material{});

			if (material.diffuseTextureName)
			{
				part.mesh.draw(TextureAsset(material.diffuseTextureName),
					PhongMaterial{ material, HasDiffuseTexture::Yes });
			}
			else
			{
				part.mesh.draw(PhongMaterial{ material, HasDiffuseTexture::No });
			}
		}
	}
}
