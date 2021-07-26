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

# include <Siv3D/OrientedBox.hpp>
# include <Siv3D/Line3D.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr std::array<size_t, 8> CornerIndices =
		{
			7, 6, 4, 5, 3, 2, 0, 1
		};
	}

	std::array<Vec3, 8> OrientedBox::getCorners() const noexcept
	{
		std::array<DirectX::XMFLOAT3, 8> corners;

		detail::FromOrientedBox(*this).GetCorners(corners.data());

		std::array<Vec3, 8> results;

		for (size_t i = 0; i < 8; ++i)
		{
			const auto& corner = corners[detail::CornerIndices[i]];

			results[i].set(corner.x, corner.y, corner.z);
		}

		return results;
	}

	const OrientedBox& OrientedBox::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), texture, color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), texture, color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), texture, color);

		return *this;
	}

	const OrientedBox& OrientedBox::drawFrame(const ColorF& color) const
	{
		const std::array<Vec3, 8> c = getCorners();

		Line3D{ c[0], c[1] }.draw(color);
		Line3D{ c[1], c[3] }.draw(color);
		Line3D{ c[3], c[2] }.draw(color);
		Line3D{ c[2], c[0] }.draw(color);

		Line3D{ c[0], c[4] }.draw(color);
		Line3D{ c[1], c[5] }.draw(color);
		Line3D{ c[2], c[6] }.draw(color);
		Line3D{ c[3], c[7] }.draw(color);

		Line3D{ c[4], c[5] }.draw(color);
		Line3D{ c[5], c[7] }.draw(color);
		Line3D{ c[7], c[6] }.draw(color);
		Line3D{ c[6], c[4] }.draw(color);

		return *this;
	}
}
