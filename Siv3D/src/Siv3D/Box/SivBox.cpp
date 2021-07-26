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

# include <Siv3D/Box.hpp>
# include <Siv3D/Line3D.hpp>
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

	void Box::_Formatter(FormatData& formatData, const Box& value)
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
