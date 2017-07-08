//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Vertex2D.hpp"
# include "Array.hpp"

namespace s3d
{
	struct Sprite
	{
		/// <summary>
		/// 頂点バッファ
		/// </summary>
		Array<Vertex2D> vertices;

		/// <summary>
		/// インデックスバッファ
		/// </summary>
		/// <remarks>
		/// サイズは 3 の倍数でなければなりません。
		/// </remarks>
		Array<uint32> indices;

		Sprite() = default;

		Sprite(uint32 vertexSize, uint32 indexSize)
			: vertices(vertexSize)
			, indices(indexSize) {}

		Sprite(Array<Vertex2D> _vertices, Array<uint32> _indices)
			: vertices(std::move(_vertices))
			, indices(std::move(_indices)) {}

		void draw() const;

		void draw(const Texture& texture) const;

		void drawSubset(uint32 startIndex, uint32 indexCount) const;

		void drawSubset(uint32 startIndex, uint32 indexCount, const Texture& texture) const;
	};
}
