//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Vertex2D.hpp"
# include "TriangleIndex.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	class Polygon;
	class Shape2D;
	class Texture;
	struct Mat3x2;

	/// @brief 2D 描画バッファ
	/// @remark 頂点とインデックス配列をユーザが作成する代わりに、2D 描画を少ないオーバーヘッドで実行できます。
	struct Buffer2D
	{
		Array<Vertex2D> vertices;

		Array<TriangleIndex> indices;

		SIV3D_NODISCARD_CXX20
		Buffer2D() = default;

		SIV3D_NODISCARD_CXX20
		Buffer2D(size_t vertexSize, size_t indexSize);

		SIV3D_NODISCARD_CXX20
		Buffer2D(Array<Vertex2D> _vertices, Array<TriangleIndex> _indices);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Polygon& polygon, const Vec2& uvOrigin, const Vec2& uvScale);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Polygon& polygon, Arg::center_<Vec2> uvCenter, const Vec2& uvScale);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Polygon& polygon, Arg::center_<Vec2> uvCenter, const Vec2& uvScale, double uvRotation);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Polygon& polygon, const Mat3x2& uvMat);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Shape2D& shape2D, const Vec2& uvOrigin, const Vec2& uvScale);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Shape2D& shape2D, Arg::center_<Vec2> uvCenter, const Vec2& uvScale);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Shape2D& shape2D, Arg::center_<Vec2> uvCenter, const Vec2& uvScale, double uvRotation);

		SIV3D_NODISCARD_CXX20
		Buffer2D(const Shape2D& shape2D, const Mat3x2& uvMat);

		void draw() const;

		void draw(const Texture& texture) const;

		void drawSubset(size_t startTriangle, size_t triangleCount) const;

		void drawSubset(size_t startTriangle, size_t triangleCount, const Texture& texture) const;
	};
}
