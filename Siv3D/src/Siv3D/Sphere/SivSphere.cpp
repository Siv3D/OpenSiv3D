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

# include <Siv3D/Sphere.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/PrimitiveMesh/IPrimitiveMesh.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
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

	void Sphere::_Formatter(FormatData& formatData, const Sphere& value)
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
