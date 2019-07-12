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
		Array<uint16> indices;

		Sprite();

		Sprite(size_t vertexSize, size_t indexSize);

		Sprite(Array<Vertex2D> _vertices, Array<uint16> _indices);

		~Sprite();

		void draw() const;

		void draw(const Texture& texture) const;

		void drawSubset(uint32 startIndex, uint32 indexCount) const;

		void drawSubset(uint32 startIndex, uint32 indexCount, const Texture& texture) const;
	};
}
