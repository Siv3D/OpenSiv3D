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

# include <Siv3D/OBB.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Triangle.hpp>

namespace s3d::experimental
{
	namespace detail
	{
		inline constexpr __m128 g_BoxOffsetHalf[8] =
		{
			{ -0.5f,  0.5f, -0.5f, 0.0f },
			{  0.5f,  0.5f, -0.5f, 0.0f },
			{ -0.5f, -0.5f, -0.5f, 0.0f },
			{  0.5f, -0.5f, -0.5f, 0.0f },
			{  0.5f,  0.5f,  0.5f, 0.0f },
			{ -0.5f,  0.5f,  0.5f, 0.0f },
			{  0.5f, -0.5f,  0.5f, 0.0f },
			{ -0.5f, -0.5f,  0.5f, 0.0f },
		};

		inline constexpr __m128 m128_UnitQuaternionEpsilon{ 1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f };

		inline bool QuaternionIsUnit(__m128 q)
		{
			__m128 Difference = SIMD::Subtract(SIMD::Vector4Length(q), SIMD::One());
			return SIMD::Vector4Less(SIMD::Abs(Difference), m128_UnitQuaternionEpsilon);
		}
	}

	void OBB::getCorners(std::array<Float3, 8>& corners) const
	{
		// Load the box
		__m128 vCenter = SIMD_Float4(center, 0.0f);
		__m128 vExtents = SIMD_Float4(size, 0.0f);
		__m128 vOrientation = orientation;

		assert(detail::QuaternionIsUnit(vOrientation));

		for (size_t i = 0; i < 8; ++i)
		{
			__m128 C = SIMD::Add(SIMD::Vector3Rotate(SIMD::Multiply(vExtents, detail::g_BoxOffsetHalf[i]), vOrientation), vCenter);
			SIMD::StoreFloat3(&corners[i], C);
		}
	}

	void OBB::draw(const Mat4x4& vp, const ColorF& color) const
	{
		constexpr size_t vertexCount = 8;
		std::array<Float3, vertexCount> vertices;
		getCorners(vertices);

		static constexpr std::array<uint32, 36> indices =
		{
			0, 1, 2, 2, 1, 3,
			5, 4, 0, 0, 4, 1,
			1, 4, 3, 3, 4, 6,
			5, 0, 7, 7, 0, 2,
			4, 5, 6, 6, 5, 7,
			2, 3, 7, 7, 3, 6,
		};

		std::array<Float3, vertexCount> out;

		SIMD::Vector3TransformCoordStream(out.data(), vertices.data(), vertexCount, vp);

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

		for (size_t i = 0; i < indices.size() / 3; ++i)
		{
			const Float3 p0 = out[indices[i * 3 + 0]];
			const Float3 p1 = out[indices[i * 3 + 1]];
			const Float3 p2 = out[indices[i * 3 + 2]];
			Triangle(p0.xy(), p1.xy(), p2.xy()).draw(color);
		}
	}
}
