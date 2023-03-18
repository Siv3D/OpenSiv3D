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

# include "Triangulation.hpp"
# include <ThirdParty/Earcut/earcut.hpp>

// Earcut s3d::Vec2 adapter
namespace mapbox::util
{
	template <>
	struct nth<0, s3d::Vec2>
	{
		inline static auto get(const s3d::Vec2& t)
		{
			return t.x;
		};
	};

	template <>
	struct nth<1, s3d::Vec2>
	{
		inline static auto get(const s3d::Vec2& t)
		{
			return t.y;
		};
	};
}

namespace s3d::detail
{
	[[nodiscard]]
	static size_t GetVertexCount(const Array<Array<Vec2>>& holes) noexcept
	{
		size_t count = 0;

		for (const auto& hole : holes)
		{
			count += hole.size();
		}

		return count;
	}

	void Triangulate(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, Array<Float2>& dstVertices, Array<Vertex2D::IndexType>& dstIndices)
	{
		Array<Vec2> vertices;
		{
			vertices.reserve(outer.size() + GetVertexCount(holes));

			vertices.append(outer);

			for (const auto& hole : holes)
			{
				vertices.append(hole);
			}
		}

		Array<Array<Vec2>> polygon;
		{
			polygon.reserve(1 + holes.size());

			polygon.push_back(outer);

			for (const auto& hole : holes)
			{
				polygon.push_back(hole);
			}
		}

		dstVertices.assign(vertices.begin(), vertices.end());
		
		dstIndices = mapbox::earcut<Vertex2D::IndexType>(polygon);
	}
}
