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

# include <Siv3D/AABB.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	void AABB::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), color);
	}

	void AABB::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), texture, color);
	}

	void AABB::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), color);
	}

	void AABB::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), texture, color);
	}
}
