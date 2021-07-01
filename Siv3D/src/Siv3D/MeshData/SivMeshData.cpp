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

# include <Siv3D/MeshData.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/FastMath.hpp>

namespace s3d
{
	namespace detail
	{
		static const Array<TriangleIndex32> OneSidedPlaceIndices
		{
			{0,1,2}, {2,1,3}
		};

		static const Array<TriangleIndex32> TwoSidedPlaceIndices
		{
			{0,1,2}, {2,1,3},
			{4,5,6}, {6,5,7}
		};

		static const Array<TriangleIndex32> BoxIndices
		{
			{0, 1, 2}, {2, 1, 3},
			{4, 5, 6}, {6, 5, 7},
			{8, 9, 10}, {10, 9, 11},
			{12, 13, 14}, {14, 13, 15},
			{16, 17, 18}, {18, 17, 19},
			{20, 21, 22}, {22, 21, 23}
		};
	}

	MeshData::MeshData(Array<Vertex3D> _vertices, Array<TriangleIndex32> _indices)
		: vertices{ std::move(_vertices) }
		, indices{ std::move(_indices) } {}

	MeshData MeshData::OneSidedPlane(const Float3 center, const Float2 size)
	{
		const Float2 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
		};

		for (auto& vertex : vertices)
		{
			vertex.pos += center;
		}

		return{ std::move(vertices), detail::OneSidedPlaceIndices };
	}

	MeshData MeshData::TwoSidedPlane(const Float3 center, const Float2 size)
	{
		const Float2 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },

			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
		};

		for (auto& vertex : vertices)
		{
			vertex.pos += center;
		}

		return{ std::move(vertices), detail::TwoSidedPlaceIndices };
	}

	MeshData MeshData::Box(const Float3 center, const Float3 size)
	{
		const Float3 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ { -s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },

			{ { s.x, s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { s.x, -s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { -s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
			{ { -s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },

			{ { -s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { -s.x, s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { -s.x, s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { -s.x, -s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { -s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		};

		if (not center.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += center;
			}
		}

		return{ std::move(vertices), detail::BoxIndices };
	}

	MeshData MeshData::Sphere(const Float3 center, const double r, const uint32 _quality)
	{
		const uint32 quality = Clamp(_quality, 4u, 100u);
		const uint32 HDIV = quality; // 半球分割数
		const uint32 DIV = HDIV * 2; // 全球分割数(偶数)
		const uint32 DIVPR = DIV + 1; // 一周あたりの頂点数
		const uint32 vsize = (DIV - 1) * DIVPR;
		const uint32 isize = DIV * 6 * HDIV;

		Array<Vertex3D> vertices(vsize);

		const float deltaU = 1.0f / DIV;
		const float deltaV = 1.0f / HDIV;
		const float deltaRU = Math::ToRadians(180.0f / HDIV);
		const float deltaRB = Math::ToRadians(360.0f / DIV);
		const float rf = static_cast<float>(r);

		for (uint32 h = 0; h <= HDIV; ++h)
		{
			for (uint32 i = 0; i < DIVPR; ++i)
			{
				const float rU = (deltaRU * h);
				const float rB = (deltaRB * i);
				const auto [su, cu] = FastMath::SinCos(rU);
				const auto [sb, cb] = FastMath::SinCos(rB);

				const float x = su * cb;
				const float y = cu;
				const float z = su * sb;

				auto& vtx = vertices[(DIVPR * h) + i];
				vtx.pos.set(x * rf, y * rf, z * rf);
				vtx.normal.set(x, y, z);
				vtx.tex.set(deltaU * i, deltaV * h);
			}
		}

		if (not center.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += center;
			}
		}

		Array<TriangleIndex32> indices(isize / 3);
		{
			TriangleIndex32* pDst = indices.data();

			for (uint32 h = 0; h < HDIV; ++h)
			{
				for (uint32 c = 0; c < DIV; ++c)
				{
					const uint32 offset = (6 * DIV) * h + c * 6;
					const uint32 idOffset = DIVPR * h + c;

					pDst->i0 = idOffset + 0;
					pDst->i1 = idOffset + 1;
					pDst->i2 = idOffset + DIVPR;
					++pDst;

					pDst->i0 = idOffset + DIVPR + 1;
					pDst->i1 = idOffset + DIVPR;
					pDst->i2 = idOffset + 1;
					++pDst;
				}
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}
}
