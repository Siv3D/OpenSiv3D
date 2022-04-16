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

# include <Siv3D/Box.hpp>
# include <Siv3D/OrientedBox.hpp>
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/Line3D.hpp>
# include <Siv3D/Triangle3D.hpp>
# include <Siv3D/ViewFrustum.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	std::array<Vec3, 8> Box::getCorners() const noexcept
	{
		const Vec3 s = (size * 0.5);

		return{
			center.movedBy(-s.x,  s.y, -s.z),
			center.movedBy( s.x,  s.y, -s.z),
			center.movedBy(-s.x, -s.y, -s.z),
			center.movedBy( s.x, -s.y, -s.z),
			
			center.movedBy(-s.x,  s.y, s.z),
			center.movedBy( s.x,  s.y, s.z),
			center.movedBy(-s.x, -s.y, s.z),
			center.movedBy( s.x, -s.y, s.z),
		};
	}

	OrientedBox Box::oriented(const Quaternion& orientation) const noexcept
	{
		return OrientedBox{ *this, orientation };
	}

	bool Box::intersects(const Vec3& point) const noexcept
	{
		return (detail::FromBox(*this).Contains(SIMD_Float4{ point, 0.0f }) == DirectX::CONTAINS);
	}

	bool Box::intersects(const Triangle3D& triangle) const noexcept
	{
		const auto b = detail::FromBox(*this);
		return b.Intersects(triangle.p0, triangle.p1, triangle.p2);
	}

	bool Box::intersects(const Sphere& sphere) const noexcept
	{
		const auto b = detail::FromBox(*this);
		return b.Intersects(detail::FromSphere(sphere));
	}

	bool Box::intersects(const Box& box) const noexcept
	{
		if (std::abs(center.x - box.center.x) > ((size.x + box.size.x) * 0.5))
		{
			return false;
		}

		if (std::abs(center.y - box.center.y) > ((size.y + box.size.y) * 0.5))
		{
			return false;
		}

		if (std::abs(center.z - box.center.z) > ((size.z + box.size.z) * 0.5))
		{
			return false;
		}

		return true;
	}

	bool Box::intersects(const OrientedBox& box) const noexcept
	{
		const auto b = detail::FromBox(*this);
		return b.Intersects(detail::FromOrientedBox(box));
	}

	bool Box::intersects(const ViewFrustum& frustum) const noexcept
	{
		const auto b = detail::FromBox(*this);
		return b.Intersects(frustum.getData());
	}

	Optional<float> Box::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}

	bool Box::contains(const Vec3& point) const noexcept
	{
		return (detail::FromBox(*this).Contains(SIMD_Float4{ point, 0.0f }) == DirectX::CONTAINS);
	}

	bool Box::contains(const Triangle3D& triangle) const noexcept
	{
		const auto b = detail::FromBox(*this);
		const auto result = b.Contains(triangle.p0, triangle.p1, triangle.p2);

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Box::contains(const Sphere& sphere) const noexcept
	{
		const auto b = detail::FromBox(*this);
		const auto result = b.Contains(detail::FromSphere(sphere));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Box::contains(const Box& box) const noexcept
	{
		const auto b = detail::FromBox(*this);
		const auto result = b.Contains(detail::FromBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Box::contains(const OrientedBox& box) const noexcept
	{
		const auto b = detail::FromBox(*this);
		const auto result = b.Contains(detail::FromOrientedBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Box::contains(const ViewFrustum& frustum) const noexcept
	{
		const auto b = detail::FromBox(*this);
		const auto result = b.Contains(frustum.getData());

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	const Box& Box::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), color);

		return *this;
	}

	const Box& Box::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), texture, color);

		return *this;
	}

	const Box& Box::draw(const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), textureRegion, color);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), color);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), texture, color);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), textureRegion, color);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), color);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), texture, color);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), textureRegion, color);

		return *this;
	}

	const Box& Box::draw(const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), material);

		return *this;
	}

	const Box& Box::draw(const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), texture, material);

		return *this;
	}

	const Box& Box::draw(const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).translated(center), textureRegion, material);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), material);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), texture, material);

		return *this;
	}

	const Box& Box::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw(Mat4x4::Scale(size).rotated(rotation).translated(center), textureRegion, material);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), material);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), texture, material);

		return *this;
	}

	const Box& Box::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Box1)
			.draw((Mat4x4::Scale(size).translated(center) * mat), textureRegion, material);

		return *this;
	}

	const Box& Box::drawFrame(const ColorF& color) const
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

	void Formatter(FormatData& formatData, const Box& value)
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

		formatData.string.append(U"))"_sv);
	}
}
