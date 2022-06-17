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
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "PolygonFailureType.hpp"
# include "Vertex2D.hpp"
# include "2DShapes.hpp"
# include "TriangleIndex.hpp"
# include "PredefinedNamedParameter.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct Buffer2D;
	struct Mat3x2;

	/// @brief 多角形
	/// @remark 穴を持つこともできます
	class Polygon
	{
	private:

		class PolygonDetail;

	public:

		SIV3D_NODISCARD_CXX20
		Polygon();

		SIV3D_NODISCARD_CXX20
		Polygon(const Polygon& polygon);

		SIV3D_NODISCARD_CXX20
		Polygon(Polygon&& polygon) noexcept;

		SIV3D_NODISCARD_CXX20
		Polygon(const Vec2* outer, size_t size, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		SIV3D_NODISCARD_CXX20
		explicit Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		SIV3D_NODISCARD_CXX20
		Polygon(const Array<Vec2>& outer, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		SIV3D_NODISCARD_CXX20
		Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		SIV3D_NODISCARD_CXX20
		explicit Polygon(std::initializer_list<Vec2> outer, SkipValidation skipValidation = SkipValidation::No);

		SIV3D_NODISCARD_CXX20
		Polygon(const Shape2D& shape);

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon) noexcept;

		/// @brief 多角形が空であるかを返します。
		/// @return  多角形が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 多角形が空ではないかを返します。
		/// @return 多角形が空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 多角形が穴を持っているかを返します。
		/// @return 穴を持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasHoles() const noexcept;

		/// @brief 多角形が持つ穴の個数を返します。
		/// @return 多角形が持つ穴の個数
		[[nodiscard]]
		size_t num_holes() const noexcept;

		void swap(Polygon& polygon) noexcept;

		/// @brief 多角形の外周の頂点配列を返します。
		/// @return 多角形の外周の頂点配列
		[[nodiscard]]
		const Array<Vec2>& outer() const noexcept;

		/// @brief 多角形の穴を構成する頂点配列を返します。
		/// @return 多角形の穴を構成する頂点配列
		[[nodiscard]]
		const Array<Array<Vec2>>& inners() const noexcept;

		/// @brief 多角形のすべての頂点を返します。
		/// @return 多角形のすべての頂点
		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		/// @brief 多角形の三角形分割のすべての頂点インデックスを返します。
		/// @remark `vertices()` の戻り値に対応します。
		/// @return 多角形の三角形分割のすべての頂点インデックス
		[[nodiscard]]
		const Array<TriangleIndex>& indices() const noexcept ;

		/// @brief 多角形のバウンディングボックスを返します。
		/// @remark バウンディングボックスは計算済みであるため、この関数のコストは小さいです。
		/// @return 多角形のバウンディングボックス
		[[nodiscard]]
		const RectF& boundingRect() const noexcept;

		/// @brief 多角形の三角形分割での三角形の個数を返します。
		/// @remark 三角形分割は計算済みであるため、この関数のコストは小さいです。
		/// @return 三角形の個数
		[[nodiscard]]
		size_t num_triangles() const noexcept;

		/// @brief 多角形の三角形分割での、個々の三角形を返します。
		/// @param index 三角形のインデックス。0 以上 `(num_triangles() - 1)` 以下
		/// @return 三角形
		[[nodiscard]]
		Triangle triangle(size_t index) const;

		/// @brief 多角形に穴を追加します。
		/// @param rect 穴の形状
		/// @return 穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const RectF& rect);

		/// @brief 多角形に穴を追加します。
		/// @param triangle 穴の形状
		/// @return  穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const Triangle& triangle);

		/// @brief 多角形に穴を追加します。
		/// @param quad 穴の形状
		/// @return  穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const Quad& quad);

		/// @brief 多角形に穴を追加します。
		/// @param circle 穴の形状
		/// @param quality 頂点分割の品質
		/// @return  穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const Circle& circle, uint32 quality = 24);

		/// @brief 多角形に穴を追加します。
		/// @param ellipse 穴の形状
		/// @param quality 頂点分割の品質
		/// @return  穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const Ellipse& ellipse, uint32 quality = 24);

		/// @brief 多角形に穴を追加します。
		/// @param roundRect 穴の形状
		/// @param quality 頂点分割の品質
		/// @return  穴の追加に成功したら true, それ以外の場合は false
		bool addHole(const RoundRect& roundRect, uint32 quality = 24);

		/// @brief 多角形に穴を追加します。
		/// @param hole 穴を構成する頂点配列
		/// @return 穴の追加に成功したら true, それ以外の場合は false
		bool addHole(Array<Vec2> hole);

		/// @brief 多角形に穴を追加します。
		/// @param holes 穴を構成する頂点配列の配列（複数の穴）
		/// @return 穴の追加に成功したら true, それ以外の場合は false
		bool addHoles(Array<Array<Vec2>> holes);

		[[nodiscard]]
		Polygon movedBy(double x, double y) const;

		[[nodiscard]]
		Polygon movedBy(Vec2 v) const;

		Polygon& moveBy(double x, double y) noexcept;

		Polygon& moveBy(Vec2 v) noexcept;

		[[nodiscard]]
		Polygon rotated(double angle) const;

		[[nodiscard]]
		Polygon rotatedAt(double x, double y, double angle) const;

		[[nodiscard]]
		Polygon rotatedAt(Vec2 pos, double angle) const;

		Polygon& rotate(double angle);

		Polygon& rotateAt(double x, double y, double angle);

		Polygon& rotateAt(Vec2 pos, double angle);

		[[nodiscard]]
		Polygon transformed(double s, double c, const Vec2& pos) const;

		Polygon& transform(double s, double c, const Vec2& pos);

		[[nodiscard]]
		Polygon scaled(double s) const;
		
		[[nodiscard]]
		Polygon scaled(double sx, double sy) const;

		[[nodiscard]]
		Polygon scaled(Vec2 s) const;

		Polygon& scale(double s);

		Polygon& scale(double sx, double sy);

		Polygon& scale(Vec2 s);

		[[nodiscard]]
		Polygon scaledAt(Vec2 pos, double s) const;

		[[nodiscard]]
		Polygon scaledAt(Vec2 pos, double sx, double sy) const;

		[[nodiscard]]
		Polygon scaledAt(Vec2 pos, Vec2 s) const;

		Polygon& scaleAt(Vec2 pos, double s);

		Polygon& scaleAt(Vec2 pos, double sx, double sy);

		Polygon& scaleAt(Vec2 pos, Vec2 s);

		/// @brief 多角形の面積を返します。
		/// @return 多角形の面積
		[[nodiscard]]
		double area() const noexcept;

		/// @brief 多角形の、穴を含めた輪郭の長さを返します。
		/// @return 多角形の、穴を含めた輪郭の長さ
		[[nodiscard]]
		double perimeter() const noexcept;

		/// @brief 多角形の重心の座標を返します。
		/// @return 多角形の重心の座標
		[[nodiscard]]
		Vec2 centroid() const;

		/// @brief 多角形の凸包を計算して返します。
		/// @return 多角形の凸包
		[[nodiscard]]
		Polygon computeConvexHull() const;

		/// @brief 多角形を太らせた、新しい多角形を返します。
		/// @param distance 太らせる距離。負の場合は細らせます。
		/// @return 新しい多角形
		[[nodiscard]]
		Polygon calculateBuffer(double distance) const;

		/// @brief 多角形を丸く太らせた、新しい多角形を返します。
		/// @param distance 太らせる距離。負の場合は細らせます。
		/// @return 新しい多角形
		[[nodiscard]]
		Polygon calculateRoundBuffer(double distance) const;

		/// @brief 多角形を単純化した、新しい多角形を返します。
		/// @param maxDistance 単純化に使う距離。大きいほど単純化されます。
		/// @return 新しい多角形
		[[nodiscard]]
		Polygon simplified(double maxDistance = 2.0) const;

		/// @brief 多角形の外周を LineString で返します。
		/// @param closeRing 始点と終点を一致させる場合は `CloseRing::Yes`, それ以外の場合は `CloseRing::No`
		/// @return 多角形の外周
		[[nodiscard]]
		LineString outline(CloseRing closeRing = CloseRing::No) const;

		/// @brief 多角形の外周の一部を LineString で返します。
		/// @param distanceFromOrigin 取得の開始位置（Polygon 外周の最初の頂点からの距離）
		/// @param length 取得する LineString の長さ
		/// @return 取得した多角形の外周の一部
		[[nodiscard]]
		LineString outline(double distanceFromOrigin, double length) const;

		/// @brief 多角形に新しい領域を追加します。新しい領域は既存の多角形と接続していなければなりません。
		/// @param other 新しい領域
		/// @return 新しい領域の追加に成功した場合 true, それ以外の場合は false
		bool append(const RectF& other);

		/// @brief 多角形に新しい領域を追加します。新しい領域は既存の多角形と接続していなければなりません。
		/// @param other 新しい領域
		/// @return 新しい領域の追加に成功した場合 true, それ以外の場合は false
		bool append(const Polygon& other);

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

		[[nodiscard]]
		bool intersects(const Line& other) const;

		[[nodiscard]]
		bool intersects(const Rect& other) const;

		[[nodiscard]]
		bool intersects(const RectF& other) const;

		[[nodiscard]]
		bool intersects(const Polygon& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		/// @brief 多角形が現在のフレームで左クリックされ始めたかを返します。
		/// @return 多角形が現在のフレームで左クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftClicked() const noexcept;

		/// @brief 多角形が左クリックされているかを返します。
		/// @return 多角形が左クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftPressed() const noexcept;

		/// @brief 現在のフレームで多角形への左クリックが離されたかを返します。
		/// @return 現在のフレームで多角形への左クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool leftReleased() const noexcept;

		/// @brief 多角形が現在のフレームで右クリックされ始めたかを返します。
		/// @return 多角形が現在のフレームで右クリックされ始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightClicked() const noexcept;

		/// @brief 多角形が右クリックされているかを返します。
		/// @return 多角形が右クリックされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightPressed() const noexcept;

		/// @brief 現在のフレームで多角形への右クリックが離されたかを返します。
		/// @return 現在のフレームで多角形への右クリックが離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool rightReleased() const noexcept;

		/// @brief 多角形上にマウスカーソルがあるかを返します。
		/// @return 多角形上にマウスカーソルがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Polygon& paint(Image& dst, const Color& color) const;

		const Polygon& paint(Image& dst, double x, double y, const Color& color) const;

		const Polygon& paint(Image& dst, const Vec2& pos, const Color& color) const;

		const Polygon& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Polygon& overwrite(Image& dst, double x, double y, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Polygon& overwrite(Image& dst, const Vec2& pos, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const Polygon& draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, const ColorF& color = Palette::White) const;

		void draw(const Vec2& pos, const ColorF& color = Palette::White) const;

		void drawTransformed(double angle, const Vec2& pos, const ColorF& color = Palette::White) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color = Palette::White) const;

		const Polygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Polygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		[[nodiscard]]
		Buffer2D toBuffer2D(const Vec2& uvOrigin, const Vec2& uvScale) const;

		[[nodiscard]]
		Buffer2D toBuffer2D(Arg::center_<Vec2> uvCenter, const Vec2& uvScale) const;

		[[nodiscard]]
		Buffer2D toBuffer2D(Arg::center_<Vec2> uvCenter, const Vec2& uvScale, double uvRotation) const;

		[[nodiscard]]
		Buffer2D toBuffer2D(const Mat3x2& uvMat) const;

		[[nodiscard]]
		static PolygonFailureType Validate(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes = {});

		[[nodiscard]]
		static PolygonFailureType Validate(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes = {});

		/// @brief 頂点配列から多角形を生成します。
		/// @param pVertex 頂点配列の先頭ポインタ
		/// @param vertexSize 頂点配列の要素数
		/// @param holes 多角形の穴
		/// @return 頂点配列から生成した多角形の配列
		[[nodiscard]]
		static Array<Polygon> Correct(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes = {});

		/// @brief 頂点配列から多角形を生成します。
		/// @param vertices 頂点配列
		/// @param holes 多角形の穴
		/// @return 頂点配列から生成した多角形の配列
		[[nodiscard]]
		static Array<Polygon> Correct(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes = {});

		[[nodiscard]]
		static Polygon CorrectOne(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes = {});

		[[nodiscard]]
		static Polygon CorrectOne(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes = {});


		[[nodiscard]]
		const PolygonDetail* _detail() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Polygon& value)
		{
			output << CharType('(');

			output << CharType('(');

			bool b = false;

			for (const auto& point : value.outer())
			{
				if (std::exchange(b, true))
				{
					output << CharType(',');
				}

				output << point;
			}

			output << CharType(')');

			if (value.inners())
			{
				output << CharType(',');

				output << CharType('(');

				b = false;

				for (const auto& hole : value.inners())
				{
					if (std::exchange(b, true))
					{
						output << CharType(',');

						output << CharType('(');
					}

					bool b2 = false;

					for (const auto& point : hole)
					{
						if (std::exchange(b2, true))
						{
							output << CharType(',');
						}

						output << point;
					}

					output << CharType(')');
				}
			}

			return output << CharType(')');
		}

		friend void Formatter(FormatData& formatData, const Polygon& value);

	private:

		std::unique_ptr<PolygonDetail> pImpl;
	};

	inline void swap(Polygon& a, Polygon& b) noexcept;
}

template <>
inline void std::swap(s3d::Polygon& a, s3d::Polygon& b) noexcept;

# include "detail/Polygon.ipp"
