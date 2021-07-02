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

# include <Siv3D/Disc.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	void Disc::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), color);
	}

	void Disc::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), texture, color);
	}

	void Disc::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), color);
	}

	void Disc::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), texture, color);
	}
}
