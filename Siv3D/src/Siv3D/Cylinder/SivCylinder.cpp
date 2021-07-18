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

# include <Siv3D/Cylinder.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	void Cylinder::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).translated(center), color);
	}

	void Cylinder::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).translated(center), texture, color);
	}

	void Cylinder::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(rotation).translated(center), color);
	}

	void Cylinder::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw(Mat4x4::Scale(Float3{ r, h, r }).rotated(rotation).translated(center), texture, color);
	}

	void Cylinder::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw((Mat4x4::Scale(Float3{ r, h, r }).translated(center) * mat), color);
	}

	void Cylinder::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Cylinder)
			.draw((Mat4x4::Scale(Float3{ r, h, r }).translated(center) * mat), texture, color);
	}
}
