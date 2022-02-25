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
# include "PointVector.hpp"
# include "TriangleIndex.hpp"
# include "2DShapes.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	class Polygon;
	struct Buffer2D;
	struct Mat3x2;

	/// @brief 多角形作成ユーティリティ
	class Shape2D
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Shape2D() = default;

		/// @brief 頂点配列と頂点インデックスから多角形を作成します。
		/// @param vertices 頂点配列
		/// @param indices 頂点インデックス
		SIV3D_NODISCARD_CXX20
		Shape2D(Array<Float2> vertices, Array<TriangleIndex> indices);

		/// @brief × の形状を作成します。
		/// @param r 基準となる円の半径（ピクセル）
		/// @param width パーツの幅（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Cross(double r, double width, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 十字形を作成します。
		/// @param r 基準となる円の半径（ピクセル）
		/// @param width パーツの幅（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Plus(double r, double width, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 正五角形を作成します。
		/// @param r 外接する円の半径（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Pentagon(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 正六角形を作成します。
		/// @param r 外接する円の半径（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Hexagon(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 正 N 角形を作成します。
		/// @param n N 角形の N (3 以上)
		/// @param r 外接する円の半径（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Ngon(uint32 n, double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 五芒星（★）を作成します。
		/// @param r 外接する円の半径（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Star(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 星形を作成します。
		/// @param n 星の先端の個数 (3 以上)
		/// @param rOuter 外側の頂点の中心からの距離（ピクセル）
		/// @param rInner 内側の頂点の中心からの距離（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D NStar(uint32 n, double rOuter, double rInner, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 矢印を作成します。
		/// @param from 矢印の始点の座標
		/// @param to 矢印の終点の座標
		/// @param width 矢印の幅（ピクセル）
		/// @param headSize 矢印の先端部分のサイズ（ピクセル）
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Arrow(const Vec2& from, const Vec2& to, double width, const Vec2& headSize);

		/// @brief 矢印を作成します。
		/// @param line 矢印の始点と終点を表す線分
		/// @param width 矢印の幅（ピクセル）
		/// @param headSize 矢印の先端部分のサイズ（ピクセル）
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Arrow(const Line& line, double width, const Vec2& headSize);

		/// @brief 両端にアローヘッドを持つ矢印を作成します。
		/// @param from 矢印の始点の座標
		/// @param to 矢印の終点の座標
		/// @param width 矢印の幅（ピクセル）
		/// @param headSize 矢印の先端部分のサイズ（ピクセル）
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D DoubleHeadedArrow(const Vec2& from, const Vec2& to, double width, const Vec2& headSize);

		/// @brief 両端にアローヘッドを持つ矢印を作成します。
		/// @param line 矢印の始点と終点を表す線分
		/// @param width 矢印の幅（ピクセル）
		/// @param headSize 矢印の先端部分のサイズ（ピクセル）
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D DoubleHeadedArrow(const Line& line, double width, const Vec2& headSize);

		/// @brief ひし形を作成します。
		/// @param w ひし形の幅
		/// @param h ひし形の高さ
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Rhombus(double w, double h, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 長方形と三角形による吹き出し形状を作成します。
		/// @param rect 長方形エリア
		/// @param target 吹き出しの先端の位置
		/// @param pointingRootRatio 吹き出しの三角形部分の大きさ [0.0, 1.0]
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D RectBalloon(const RectF& rect, const Vec2& target, double pointingRootRatio = 0.5);

		/// @brief 階段の形状を作成します。
		/// @param base 階段の基準位置
		/// @param w 階段全体の幅
		/// @param h 階段全体の高さ
		/// @param steps 階段の段数
		/// @param upStairs 右上に上る向きであるか
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Stairs(const Vec2& base, double w, double h, uint32 steps, bool upStairs = true);

		/// @brief ハート形を作成します。
		/// @param r 外接する円の半径（ピクセル）
		/// @param center 中心座標
		/// @param angle 時計回りの回転角度
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Heart(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		/// @brief 正方形と円の中間の形状 (Squircle) を作成します。
		/// @param r 円の半径
		/// @param center 中心座標
		/// @param quality 品質
		/// @return 作成した形状
		[[nodiscard]]
		static Shape2D Squircle(double r, const Vec2& center, uint32 quality);

		/// @brief 頂点座標の配列を返します。
		/// @return 頂点座標の配列
		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		/// @brief 頂点インデックスの配列を返します。
		/// @return 頂点インデックスの配列
		[[nodiscard]]
		const Array<TriangleIndex> indices() const noexcept;

		/// @brief 図形を描画します。
		/// @param color 色
		/// @return *this
		const Shape2D& draw(const ColorF& color = Palette::White) const;

		/// @brief 図形の枠を描画します。
		/// @param thickness 枠の太さ
		/// @param color 色
		/// @return *this
		const Shape2D& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 図形を構成する三角形をワイヤフレームで描画します。
		/// @param thickness ワイヤフレームの太さ
		/// @param color 色
		/// @return *this
		const Shape2D& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 図形を Polygon として返します。
		/// @return 図形の Polygon
		[[nodiscard]] 
		Polygon asPolygon() const;

		/// @brief 図形に UV 座標をマッピングして Buffer2D を作成します。
		/// @param uvOrigin UV 座標 (0, 0) をマッピングする位置
		/// @param uvScale マッピングする UV のスケール
		/// @return Buffer2D
		[[nodiscard]]
		Buffer2D toBuffer2D(const Vec2& uvOrigin, const Vec2& uvScale) const;

		/// @brief 図形に UV 座標をマッピングして Buffer2D を作成します。
		/// @param uvCenter UV 座標 (0.5, 0.5) をマッピングする位置
		/// @param uvScale マッピングする UV のスケール
		/// @return Buffer2D
		[[nodiscard]]
		Buffer2D toBuffer2D(Arg::center_<Vec2> uvCenter, const Vec2& uvScale) const;

		/// @brief 図形に UV 座標をマッピングして Buffer2D を作成します。
		/// @param uvCenter UV 座標 (0.5, 0.5) をマッピングする位置
		/// @param uvScale マッピングする UV のスケール
		/// @param uvRotation マッピングする UV の時計回りの回転
		/// @return Buffer2D
		[[nodiscard]]
		Buffer2D toBuffer2D(Arg::center_<Vec2> uvCenter, const Vec2& uvScale, double uvRotation) const;

		/// @brief 図形に UV 座標をマッピングして Buffer2D を作成します。
		/// @param uvMat 頂点の座標から UV 座標を計算する行列
		/// @return Buffer2D
		[[nodiscard]]
		Buffer2D toBuffer2D(const Mat3x2& uvMat) const;

	private:

		Array<Float2> m_vertices;

		Array<TriangleIndex> m_indices;
	};
}

# include "detail/Shape2D.ipp"
