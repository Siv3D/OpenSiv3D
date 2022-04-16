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

# include <Siv3D/OrientedBox.hpp>
# include <Siv3D/Line3D.hpp>
# include <Siv3D/Triangle3D.hpp>
# include <Siv3D/ViewFrustum.hpp>
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

	bool OrientedBox::intersects(const Vec3& point) const noexcept
	{
		return (detail::FromOrientedBox(*this).Contains(SIMD_Float4{ point, 0.0f }) == DirectX::CONTAINS);
	}

	bool OrientedBox::intersects(const Triangle3D& triangle) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		return b.Intersects(triangle.p0, triangle.p1, triangle.p2);
	}

	bool OrientedBox::intersects(const Sphere& sphere) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		return b.Intersects(detail::FromSphere(sphere));
	}

	bool OrientedBox::intersects(const Box& box) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		return b.Intersects(detail::FromBox(box));
	}

	bool OrientedBox::intersects(const OrientedBox& box) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		return b.Intersects(detail::FromOrientedBox(box));
	}

	bool OrientedBox::intersects(const ViewFrustum& frustum) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		return b.Intersects(frustum.getData());
	}

	Optional<float> OrientedBox::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}

	bool OrientedBox::contains(const Vec3& point) const noexcept
	{
		return (detail::FromOrientedBox(*this).Contains(SIMD_Float4{ point, 0.0f }) == DirectX::CONTAINS);
	}

	bool OrientedBox::contains(const Triangle3D& triangle) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		const auto result = b.Contains(triangle.p0, triangle.p1, triangle.p2);

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool OrientedBox::contains(const Sphere& sphere) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		const auto result = b.Contains(detail::FromSphere(sphere));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool OrientedBox::contains(const Box& box) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		const auto result = b.Contains(detail::FromBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool OrientedBox::contains(const OrientedBox& box) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		const auto result = b.Contains(detail::FromOrientedBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool OrientedBox::contains(const ViewFrustum& frustum) const noexcept
	{
		const auto b = detail::FromOrientedBox(*this);
		const auto result = b.Contains(frustum.getData());

		return (result == DirectX::ContainmentType::CONTAINS);
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

	const OrientedBox& OrientedBox::draw(const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), textureRegion, color);

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

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), textureRegion, color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), textureRegion, color);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), texture, color);

		return *this;
	}


	const OrientedBox& OrientedBox::draw(const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), texture, material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation).translated(center), textureRegion, material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), texture, material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(orientation * rotation).translated(center), textureRegion, material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), texture, material);

		return *this;
	}

	const OrientedBox& OrientedBox::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).rotated(orientation).translated(center) * mat), textureRegion, material);

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

	void Formatter(FormatData& formatData, const OrientedBox& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.center.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.center.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.center.z, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.size.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.size.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.size.z, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		const Float4 o = value.orientation.toFloat4();
		formatData.string.append(ToString(o.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.w, formatData.decimalPlaces.value));

		formatData.string.append(U"))"_sv);
	}
}
