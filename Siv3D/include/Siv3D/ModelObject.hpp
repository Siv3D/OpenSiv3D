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
# include "Array.hpp"
# include "String.hpp"
# include "ModelMeshPart.hpp"
# include "Box.hpp"
# include "Sphere.hpp"
# include "Material.hpp"

namespace s3d
{
	struct ModelObject
	{
		String name;

		Array<ModelMeshPart> parts;

		Sphere boundingSphere{ 0.0 };

		Box boundingBox{ 0.0 };

		void draw(const Array<Material>& materials) const;
	};
}
