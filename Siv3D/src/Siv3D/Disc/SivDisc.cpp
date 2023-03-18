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

# include <Siv3D/Disc.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	const Disc& Disc::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), color);

		return *this;
	}

	const Disc& Disc::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), texture, color);

		return *this;
	}

	const Disc& Disc::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), color);

		return *this;
	}

	const Disc& Disc::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), texture, color);

		return *this;
	}

	const Disc& Disc::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw((Mat4x4::Scale(Float3{ r, 1, r }).translated(center) * mat), color);

		return *this;
	}

	const Disc& Disc::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw((Mat4x4::Scale(Float3{ r, 1, r }).translated(center) * mat), texture, color);

		return *this;
	}


	const Disc& Disc::draw(const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), material);

		return *this;
	}

	const Disc& Disc::draw(const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).translated(center), texture, material);

		return *this;
	}

	const Disc& Disc::draw(const Quaternion& rotation, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), material);

		return *this;
	}

	const Disc& Disc::draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw(Mat4x4::Scale(Float3{ r, 1, r }).rotated(rotation).translated(center), texture, material);

		return *this;
	}

	const Disc& Disc::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw((Mat4x4::Scale(Float3{ r, 1, r }).translated(center) * mat), material);

		return *this;
	}

	const Disc& Disc::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Disc)
			.draw((Mat4x4::Scale(Float3{ r, 1, r }).translated(center) * mat), texture, material);

		return *this;
	}
}
