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
# include <Siv3D/Vertex2D.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr __m128 BoxOffsetHalf[8] =
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

		constexpr std::array<uint16, 36> Indices =
		{
			0, 1, 2, 2, 1, 3,
			5, 4, 0, 0, 4, 1,
			1, 4, 3, 3, 4, 6,
			5, 0, 7, 7, 0, 2,
			4, 5, 6, 6, 5, 7,
			2, 3, 7, 7, 3, 6,
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
			__m128 C = SIMD::Add(SIMD::Vector3Rotate(SIMD::Multiply(vExtents, detail::BoxOffsetHalf[i]), vOrientation), vCenter);
			SIMD::StoreFloat3(&corners[i], C);
		}
	}

	void OBB::draw(const Mat4x4& vp, const ColorF& color) const
	{
		constexpr size_t vertexCount = 8;
		const Float2 resolution = Graphics2D::GetRenderTargetSize();
		const Float4 colorF = color.toFloat4();

		std::array<Float3, vertexCount> corners;
		getCorners(corners);

		std::array<Float3, vertexCount> out;
		SIMD::Vector3TransformCoordStream(out.data(), corners.data(), vertexCount, vp);

		for (auto& v : out)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		std::array<Vertex2D, vertexCount> vertices;
		for (size_t i = 0; i < vertexCount; ++i)
		{
			auto& v = vertices[i];
			v.pos = out[i].xy();
			v.color = colorF;
		}

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(vertices.data(), vertices.size(), detail::Indices.data(), detail::Indices.size());
	}
}
