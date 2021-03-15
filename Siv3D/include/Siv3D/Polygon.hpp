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

	class Polygon
	{
	private:

		class PolygonDetail;

	public:

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon) noexcept;

		Polygon(const Vec2* outer, size_t size, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		explicit Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		Polygon(const Array<Vec2>& outer, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		explicit Polygon(std::initializer_list<Vec2> outer, SkipValidation skipValidation = SkipValidation::No);

		Polygon(const Shape2D& shape);

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool hasHoles() const noexcept;

		[[nodiscard]]
		size_t num_holes() const noexcept;

		void swap(Polygon& polygon) noexcept;

		[[nodiscard]]
		const Array<Vec2>& outer() const noexcept;

		[[nodiscard]]
		const Array<Array<Vec2>>& inners() const noexcept;

		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		[[nodiscard]]
		const Array<TriangleIndex>& indices() const noexcept ;

		[[nodiscard]]
		const RectF& boundingRect() const noexcept;

		[[nodiscard]]
		size_t num_triangles() const noexcept;

		[[nodiscard]]
		Triangle triangle(size_t index) const;

		Polygon& addHole(Array<Vec2> hole, SkipValidation skipValidation = SkipValidation::No);

		Polygon& addHoles(Array<Array<Vec2>> holes, SkipValidation skipValidation = SkipValidation::No);

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

		Polygon& scale(double s);

		[[nodiscard]]
		Polygon scaled(Vec2 s) const;

		Polygon& scale(Vec2 s);

		[[nodiscard]]
		Polygon scaledAt(Vec2 pos, double s);

		Polygon& scaleAt(Vec2 pos, double s);

		[[nodiscard]]
		Polygon scaledAt(Vec2 pos, Vec2 s) const;

		Polygon& scaleAt(Vec2 pos, Vec2 s);

		[[nodiscard]]
		double area() const noexcept;

		[[nodiscard]]
		double perimeter() const noexcept;

		[[nodiscard]]
		Vec2 centroid() const;

		[[nodiscard]]
		Polygon calculateConvexHull() const;

		[[nodiscard]]
		Polygon calculateBuffer(double distance) const;

		[[nodiscard]]
		Polygon calculateRoundBuffer(double distance) const;

		[[nodiscard]]
		Polygon simplified(double maxDistance = 2.0) const;

		[[nodiscard]]
		LineString outline(CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		LineString outline(double distanceFromOrigin, double length) const;

		bool append(const RectF& other);

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

		[[nodiscard]]
		bool leftClicked() const noexcept;

		[[nodiscard]]
		bool leftPressed() const noexcept;

		[[nodiscard]]
		bool leftReleased() const noexcept;

		[[nodiscard]]
		bool rightClicked() const noexcept;

		[[nodiscard]]
		bool rightPressed() const noexcept;

		[[nodiscard]]
		bool rightReleased() const noexcept;

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

		[[nodiscard]]
		static Array<Polygon> Correct(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes = {});

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

		friend void Formatter(FormatData& formatData, const Polygon& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Polygon& value);

	private:

		std::unique_ptr<PolygonDetail> pImpl;
	};

	inline void swap(Polygon& a, Polygon& b) noexcept;
}

template <>
inline void std::swap(s3d::Polygon& a, s3d::Polygon& b) noexcept;

# include "detail/Polygon.ipp"
