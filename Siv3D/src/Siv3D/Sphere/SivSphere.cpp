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

# include <Siv3D/Sphere.hpp>
# include <Siv3D/Triangle3D.hpp>
# include <Siv3D/ViewFrustum.hpp>
# include <Siv3D/Ray.hpp>
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	bool Sphere::intersects(const Vec3& point) const noexcept
	{
		const double distanceSq = point.distanceFromSq(center);
		const double radiusSq = (r * r);
		return (distanceSq <= radiusSq);
	}

	bool Sphere::intersects(const Triangle3D& triangle) const noexcept
	{
		const auto sphere = detail::FromSphere(*this);
		return sphere.Intersects(triangle.p0, triangle.p1, triangle.p2);
	}

	bool Sphere::intersects(const Sphere& sphere) const noexcept
	{
		const double distanceSq = center.distanceFrom(sphere.center);
		const double radiusSum = (r + sphere.r);
		return (distanceSq <= (radiusSum * radiusSum));
	}

	bool Sphere::intersects(const Box& box) const noexcept
	{
		return detail::FromBox(box).Intersects(detail::FromSphere(*this));
	}

	bool Sphere::intersects(const OrientedBox& box) const noexcept
	{
		return detail::FromOrientedBox(box).Intersects(detail::FromSphere(*this));
	}

	bool Sphere::intersects(const ViewFrustum& frustum) const noexcept
	{
		return frustum.getData().Intersects(detail::FromSphere(*this));
	}

	Optional<float> Sphere::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}

	bool Sphere::contains(const Vec3& point) const noexcept
	{
		const double distanceSq = point.distanceFromSq(center);
		const double radiusSq = (r * r);
		return (distanceSq < radiusSq);
	}

	bool Sphere::contains(const Triangle3D& triangle) const noexcept
	{
		const auto sphere = detail::FromSphere(*this);
		const auto result = sphere.Contains(triangle.p0, triangle.p1, triangle.p2);

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Sphere::contains(const Sphere& sphere) const noexcept
	{
		return (sphere.r < r)
			&& (center.distanceFromSq(sphere.center) <= ((r - sphere.r) * (r - sphere.r)));
	}

	bool Sphere::contains(const Box& box) const noexcept
	{
		const auto sphere = detail::FromSphere(*this);
		const auto result = sphere.Contains(detail::FromBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Sphere::contains(const OrientedBox& box) const noexcept
	{
		const auto sphere = detail::FromSphere(*this);
		const auto result = sphere.Contains(detail::FromOrientedBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool Sphere::contains(const ViewFrustum& frustum) const noexcept
	{
		const auto sphere = detail::FromSphere(*this);
		const auto result = sphere.Contains(frustum.getData());

		return (result == DirectX::ContainmentType::CONTAINS);
	}




	const Sphere& Sphere::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).translated(center), color);

		return *this;
	}

	const Sphere& Sphere::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).translated(center), texture, color);

		return *this;
	}

	const Sphere& Sphere::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).rotated(rotation).translated(center), color);

		return *this;
	}

	const Sphere& Sphere::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).rotated(rotation).translated(center), texture, color);

		return *this;
	}

	const Sphere& Sphere::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw((Mat4x4::Scale(r).translated(center) * mat), color);

		return *this;
	}

	const Sphere& Sphere::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw((Mat4x4::Scale(r).translated(center) * mat), texture, color);

		return *this;
	}



	const Sphere& Sphere::draw(const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).translated(center), material);

		return *this;
	}

	const Sphere& Sphere::draw(const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).translated(center), texture, material);

		return *this;
	}

	const Sphere& Sphere::draw(const Quaternion& rotation, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).rotated(rotation).translated(center), material);

		return *this;
	}

	const Sphere& Sphere::draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw(Mat4x4::Scale(r).rotated(rotation).translated(center), texture, material);

		return *this;
	}

	const Sphere& Sphere::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw((Mat4x4::Scale(r).translated(center) * mat), material);

		return *this;
	}

	const Sphere& Sphere::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::Sphere)
			.draw((Mat4x4::Scale(r).translated(center) * mat), texture, material);

		return *this;
	}

	void Formatter(FormatData& formatData, const Sphere& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.center.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.center.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.center.z, formatData.decimalPlaces.value));
		formatData.string.append(U"), "_sv);

		formatData.string.append(ToString(value.r, formatData.decimalPlaces.value));

		formatData.string.append(U")"_sv);
	}
}
