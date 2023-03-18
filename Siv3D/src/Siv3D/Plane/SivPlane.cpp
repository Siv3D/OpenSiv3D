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

# include <Siv3D/Plane.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Ray.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Optional<float> Plane::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}

	const Plane& Plane::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), color);

		return *this;
	}

	const Plane& Plane::draw(const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), texture, color);

		return *this;
	}

	const Plane& Plane::draw(const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), textureRegion, color);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), color);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), texture, color);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), textureRegion, color);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), color);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), texture, color);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), textureRegion, color);

		return *this;
	}


	const Plane& Plane::draw(const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), material);

		return *this;
	}

	const Plane& Plane::draw(const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), texture, material);

		return *this;
	}

	const Plane& Plane::draw(const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center), textureRegion, material);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), material);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), texture, material);

		return *this;
	}

	const Plane& Plane::draw(const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw(Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).rotated(rotation).translated(center), textureRegion, material);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), material);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), texture, material);

		return *this;
	}

	const Plane& Plane::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		SIV3D_ENGINE(PrimitiveMesh)->getMesh(PrimitiveMeshType::TwoSidedPlane)
			.draw((Mat4x4::Scale(Float3{ size.x, 1.0f, size.y }).translated(center) * mat), textureRegion, material);

		return *this;
	}

	void Formatter(FormatData& formatData, const Plane& value)
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

		formatData.string.append(U"))"_sv);
	}
}
