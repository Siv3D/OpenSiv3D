//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Triangle3D.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Triangle.hpp>

namespace s3d::experimental
{
	void Triangle3D::draw(const Mat4x4& vp, const ColorF& color) const
	{
		constexpr size_t vertexCount = 3;
		const Float3 vec[vertexCount] = { p0, p1, p2 };
		Float3 out[vertexCount];

		SIMD::Vector3TransformCoordStream(out, vec, vertexCount, vp);

		const Float2 resolution = Graphics2D::GetRenderTargetSize();

		for (auto& v : out)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		Triangle(out[0].xy(), out[1].xy(), out[2].xy()).draw(color);
	}


	void SIMD_Triangle3D::draw(const Mat4x4& vp, const ColorF& color) const
	{
		constexpr size_t vertexCount = 3;
		Float3 out[vertexCount];

		SIMD::Vector3TransformCoordStream(out, vec, vertexCount, vp);

		const Float2 resolution = Graphics2D::GetRenderTargetSize();

		for (auto& v : out)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		Triangle(out[0].xy(), out[1].xy(), out[2].xy()).draw(color);
	}
}
